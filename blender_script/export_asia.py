# exporte une scene Blender 2.49 vers un fichier XML 
# respectant le schema raytracer.xsd

import Blender

class Balise:
	""" permet de sortir des donnees sous forme de balises xml """
	def __init__(self, nom):
		self.nom = nom
		self.param = ""
	def addParam(self, name, param):
		self.param += ' ' + name + '="' + str(param)	+ '"'
	def addParamDouble(self, name, param):
		self.param += ' ' + name + '="' + str(round(param, 6))	+ '"'
	def beginEnd(self, fichier):
		fichier.write('<' + self.nom + self.param + '/>\n')
	def begin(self, fichier):
		fichier.write('<' + self.nom + self.param + '>\n')
	def end(self, fichier):
		fichier.write( '</' + self.nom + '>\n')

def copierImage(imageSrc, cheminDst):
	""" copie une image Blender dans un fichier au repertoire donne """
	fichierImage = imageSrc.getFilename()
	nomImage = Blender.sys.basename(fichierImage)
	cheminImage = Blender.sys.dirname(fichierImage)
	imageSrc.setFilename(Blender.sys.join(cheminDst, nomImage))
	imageSrc.save()
	imageSrc.setFilename(fichierImage)
	return nomImage
	
def fonctionExportation(nomFichier):
	chemin = Blender.sys.dirname(nomFichier)
	# exporte la scene courante dans un fichier XML
	fichier = open(nomFichier, 'w')
	fichier.write('<?xml version="1.0"?>\n')
	bScene = Balise('scene')
	bScene.begin(fichier)
	scene = Blender.Scene.GetCurrent()
	objets = scene.objects

	# exporte les cameras
	objetsCamera = [o for o in objets if o.type == 'Camera']
	for o in objetsCamera:
		c = o.getData()
		if c.type.lower() == 'persp':
			bCamera = Balise('camera')
			bCamera.addParam('nom', o.getName())
			bCamera.begin(fichier)
			bCameraPinhole = Balise('camera_pinhole')
			bCameraPinhole.addParamDouble('position_x', o.LocX)
			bCameraPinhole.addParamDouble('position_y', o.LocY)
			bCameraPinhole.addParamDouble('position_z', o.LocZ)
			bCameraPinhole.addParamDouble('visee_x', -o.mat[2][0])
			bCameraPinhole.addParamDouble('visee_y', -o.mat[2][1])
			bCameraPinhole.addParamDouble('visee_z', -o.mat[2][2])
			bCameraPinhole.addParamDouble('verticale_x', o.mat[1][0])
			bCameraPinhole.addParamDouble('verticale_y', o.mat[1][1])
			bCameraPinhole.addParamDouble('verticale_z', o.mat[1][2])
			bCameraPinhole.addParamDouble('xfov', c.angle)
			bCameraPinhole.beginEnd(fichier)
			bCamera.end(fichier)
			
	# exporte les lumieres
	objetsLamp = [o for o in objets if o.type == 'Lamp']
	for o in objetsLamp:
		l = o.getData()
		if l.type == 0:
			bLumiere = Balise('lumiere')
			bLumiere.addParam('nom', o.getName())
			bLumiere.begin(fichier)
			bLumierePoint = Balise('lumiere_point')
			bLumierePoint.addParamDouble('position_x', o.LocX)
			bLumierePoint.addParamDouble('position_y', o.LocY)
			bLumierePoint.addParamDouble('position_z', o.LocZ)
			bLumierePoint.addParamDouble('couleur_r', l.R)
			bLumierePoint.addParamDouble('couleur_g', l.G)
			bLumierePoint.addParamDouble('couleur_b', l.B)
			bLumierePoint.beginEnd(fichier)
			bLumiere.end(fichier)
		
	# exporte les objets
	ambiant = [0, 0, 0]
	if scene.world is not None:
		ambiant = scene.world.amb
	objetsMesh = [o for o in objets if o.type == 'Mesh']
	for o in objetsMesh:
		h = o.getData()
		# materiau
		# recupere le premier materiau de type phong (diffus lambert + speculaire phong)
		mList = [m for m in h.materials if m is not None and m.diffuseShader==Blender.Material.Shaders['DIFFUSE_LAMBERT'] and m.specShader==Blender.Material.Shaders['SPEC_PHONG']]
		if len(mList) > 0:
			bObjet = Balise('objet')
			bObjet.addParam('nom', o.getName())
			bObjet.begin(fichier)
			m = mList[0]
			if m.mode & Blender.Material.Modes['RAYMIRROR']:
				bMateriau = Balise('materiau_miroir')
			else:
				bMateriau = Balise('materiau_phong')	
			bMateriau.addParam('nom', m.getName())		
			bMateriau.addParam('ns', m.hard*0.1)
			bMateriau.begin(fichier)
			tList = [t for t in m.getTextures() if t is not None]
			
			# ambiant
			taList = [t for t in tList if t.mapto & Blender.Texture.MapTo['AMB'] and t.tex.type & Blender.Texture.Types['IMAGE']]
			if len(taList) == 0:
				bMateriauA = Balise('materiau_ca')
				bMateriauA.addParamDouble('r', ambiant[0]*m.amb)
				bMateriauA.addParamDouble('g', ambiant[1]*m.amb)
				bMateriauA.addParamDouble('b', ambiant[2]*m.amb)
				bMateriauA.beginEnd(fichier)
			else:
				bMateriauA = Balise('materiau_ta')
				nomImage = copierImage(tdList[0].tex.image, chemin)
				bMateriauA.addParam('image',nomImage)
				bMateriauA.beginEnd(fichier)
			
			# diffus
			tdList = [t for t in tList if t.mapto & Blender.Texture.MapTo['COL'] and t.tex.type & Blender.Texture.Types['IMAGE']]
			if len(tdList) == 0:
				bMateriauD = Balise('materiau_cd')
				bMateriauD.addParamDouble('r', m.R)
				bMateriauD.addParamDouble('g', m.G)
				bMateriauD.addParamDouble('b', m.B)
				bMateriauD.beginEnd(fichier)
			else:
				bMateriauD = Balise('materiau_td')
				nomImage = copierImage(tdList[0].tex.image, chemin)
				bMateriauD.addParam('image',nomImage)
				bMateriauD.beginEnd(fichier)
			
			# speculaire
			tsList = [t for t in tList if t.mapto & Blender.Texture.MapTo['SPEC'] and t.tex.type & Blender.Texture.Types['IMAGE']]
			if len(tsList) == 0:
				bMateriauS = Balise('materiau_cs')
				bMateriauS.addParamDouble('r', m.specR)
				bMateriauS.addParamDouble('g', m.specG)
				bMateriauS.addParamDouble('b', m.specB)
				bMateriauS.beginEnd(fichier)
			else:
				bMateriauS = Balise('materiau_ts')
				nomImage = copierImage(tdList[0].tex.image, chemin)
				bMateriauS.addParam('image',nomImage)
				bMateriauS.beginEnd(fichier)
			
			# miroir
			if m.mode & Blender.Material.Modes['RAYMIRROR']:
				tsList = [t for t in tList if t.mapto & Blender.Texture.MapTo['RAYMIR'] and t.tex.type & Blender.Texture.Types['IMAGE']]
				if len(tsList) == 0:
					bMateriauS = Balise('materiau_cr')
					bMateriauS.addParamDouble('r', m.mirR)
					bMateriauS.addParamDouble('g', m.mirG)
					bMateriauS.addParamDouble('b', m.mirB)
					bMateriauS.beginEnd(fichier)
				else:
					bMateriauS = Balise('materiau_tr')
					nomImage = copierImage(tdList[0].tex.image, chemin)
					bMateriauS.addParam('image',nomImage)
					bMateriauS.beginEnd(fichier)
			
			bMateriau.end(fichier)
			
			# triangles
			faces = h.faces
			old_verts = h.verts[:]
			# transforme les sommets dans le repere monde
			h.transform(o.matrix, True)
			# parcourt les faces
			for iface in xrange(len(faces)):
				bTriangle = Balise('primitive_triangle')
				bTriangle.begin(fichier)
				f = faces[iface]
				if len(f) >= 3:
					# parcourt les sommets
					for ivert in xrange(3):
						v = f[ivert]
						if f.smooth:
							n = v.no
						else:
							n = f.no
						if len(f.uv)==0:
							t = [0, 0]
						else:
							t = f.uv[ivert]
						bSommet = Balise('sommet')
						bSommet.addParamDouble('position_x', v.co[0])
						bSommet.addParamDouble('position_y', v.co[1])
						bSommet.addParamDouble('position_z', v.co[2])
						bSommet.addParamDouble('normale_x', n[0])
						bSommet.addParamDouble('normale_y', n[1])
						bSommet.addParamDouble('normale_z', n[2])
						bSommet.addParamDouble('texcoords_u', t[0])
						bSommet.addParamDouble('texcoords_v', t[1])					
						bSommet.beginEnd(fichier)
				bTriangle.end(fichier)
			h.verts = old_verts
			bObjet.end(fichier)
	bScene.end(fichier)
	fichier.close()
	print 'ok'

# ouvre une boite de dialogue pour choisir le fichier a ecrire
# et lance l'exportation
Blender.Window.FileSelector(fonctionExportation, 'Export file', 'scene.xml')
