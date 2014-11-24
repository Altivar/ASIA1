#include "Loader.h"

#include <iostream>

#include <QXmlDefaultHandler>
#include <QXmlSimpleReader>
#include <QXmlInputSource>

#include <QXmlSchema>
#include <QXmlSchemaValidator>


class Handler : public QXmlDefaultHandler
{
	Scene &_scene;
	String _chemin;

	// pour camera, lumiere, materiau
	String _nom;

	// pour materiau
	Texture *_textureAmbiant;
	Texture *_textureDiffus;
	Texture *_textureSpeculaire;
	Texture *_textureMiroir;
	reel _textureNs;

	// pour primitive
	Materiau *_materiau;

	// pour primitive triangle
	std::vector<Sommet> _sommets;

public:
	Handler(Scene &scene, const String &chemin):
		_scene(scene), _chemin(chemin)
	{}

	bool startElement( const QString & , const QString & , const QString & qName, const QXmlAttributes & atts )
	{
		if( qName=="camera" || qName=="lumiere" )
		{
			_nom = String(atts.value("nom").toAscii());
			return true;
		}
		if( qName == "camera_pinhole" )
		{
			reel px = atts.value("position_x").toDouble();
			reel py = atts.value("position_y").toDouble();
			reel pz = atts.value("position_z").toDouble();
			reel vx = atts.value("visee_x").toDouble();
			reel vy = atts.value("visee_y").toDouble();
			reel vz = atts.value("visee_z").toDouble();
			reel ux = atts.value("verticale_x").toDouble();
			reel uy = atts.value("verticale_y").toDouble();
			reel uz = atts.value("verticale_z").toDouble();
			reel xfov = atts.value("xfov").toDouble();
			Camera *camera = new CameraPinhole(Vecteur3(px, py, pz), Vecteur3(vx, vy, vz), Vecteur3(ux, uy, uz), xfov);
			_scene.enregistrerCamera(camera);
			camera->_nom = _nom;
			return true;
		}
		if( qName == "lumiere_point" )
		{
			reel x = atts.value("position_x").toDouble();
			reel y = atts.value("position_y").toDouble();
			reel z = atts.value("position_z").toDouble();
			reel r = atts.value("couleur_r").toDouble();
			reel g = atts.value("couleur_g").toDouble();
			reel b = atts.value("couleur_b").toDouble();
			Lumiere *lumiere = (Lumiere *) new LumierePoint(Vecteur3(x, y, z), Couleur(r, g, b, 1));
			_scene.enregistrerLumiere(lumiere);
			lumiere->_nom = _nom;
			return true;
		}
		if( qName == "materiau_ca" )
		{
			reel r = atts.value("r").toDouble();
			reel g = atts.value("g").toDouble();
			reel b = atts.value("b").toDouble();
			_textureAmbiant = new TextureCouleur(Couleur(r, g, b, 1));
			_scene.enregistrerTexture(_textureAmbiant);
			return true;
		}
		if( qName == "materiau_ta" )
		{
			String nomImage(atts.value("image").toAscii());
			Image *image = _scene.enregistrerImage(_chemin+nomImage);
			_textureAmbiant = new TextureImage(image);
			_scene.enregistrerTexture(_textureAmbiant);
			return true;
		}
		if( qName == "materiau_cd" )
		{
			reel r = atts.value("r").toDouble();
			reel g = atts.value("g").toDouble();
			reel b = atts.value("b").toDouble();
			_textureDiffus = new TextureCouleur(Couleur(r, g, b, 1));
			_scene.enregistrerTexture(_textureDiffus);
			return true;
		}
		if( qName == "materiau_td" )
		{
			String nomImage(atts.value("image").toAscii());
			Image *image = _scene.enregistrerImage(_chemin+nomImage);
			_textureDiffus = new TextureImage(image);
			_scene.enregistrerTexture(_textureDiffus);
			return true;
		}
		if( qName == "materiau_cs" )
		{
			reel r = atts.value("r").toDouble();
			reel g = atts.value("g").toDouble();
			reel b = atts.value("b").toDouble();
			_textureSpeculaire = new TextureCouleur(Couleur(r, g, b, 1));
			_scene.enregistrerTexture(_textureSpeculaire);
			return true;
		}
		if( qName == "materiau_ts" )
		{
			String nomImage(atts.value("image").toAscii());
			Image *image = _scene.enregistrerImage(_chemin+nomImage);
			_textureSpeculaire = new TextureImage(image);
			_scene.enregistrerTexture(_textureSpeculaire);
			return true;
		}
		if( qName == "materiau_cr" )
		{
			reel r = atts.value("r").toDouble();
			reel g = atts.value("g").toDouble();
			reel b = atts.value("b").toDouble();
			_textureMiroir = new TextureCouleur(Couleur(r, g, b, 1));
			_scene.enregistrerTexture(_textureMiroir);
			return true;
		}
		if( qName == "materiau_tr" )
		{
			String nomImage(atts.value("image").toAscii());
			Image *image = _scene.enregistrerImage(_chemin+nomImage);
			_textureMiroir = new TextureImage(image);
			_scene.enregistrerTexture(_textureMiroir);
			return true;
		}
		if( qName == "materiau_phong" || qName == "materiau_miroir" )
		{
			_nom = String(atts.value("nom").toAscii());
			_textureNs = atts.value("ns").toDouble();
			return true;
		}
		if( qName == "primitive_sphere" )
		{
			reel x = atts.value("centre_x").toDouble();
			reel y = atts.value("centre_y").toDouble();
			reel z = atts.value("centre_z").toDouble();
			reel r = atts.value("rayon").toDouble();
			Primitive *primitive = new PrimitiveSphere(_materiau, Vecteur3(x, y, z), r);
			_scene.enregistrerPrimitive(primitive);
			return true;
		}
		if( qName == "primitive_triangle" )
		{
			_sommets.clear();
			return true;
		}
		if( qName == "sommet" )
		{
			reel px = atts.value("position_x").toDouble();
			reel py = atts.value("position_y").toDouble();
			reel pz = atts.value("position_z").toDouble();
			reel nx = atts.value("normale_x").toDouble();
			reel ny = atts.value("normale_y").toDouble();
			reel nz = atts.value("normale_z").toDouble();
			reel tu = atts.value("texcoords_u").toDouble();
			reel tv = atts.value("texcoords_v").toDouble();
			_sommets.push_back(Sommet(Vecteur3(px, py, pz), Vecteur3(nx, ny, nz), Vecteur2(tu, tv)));
			return true;
		}
		return true;
	}

	bool endElement(const QString &, const QString &, const QString & qName)
	{
		if( qName == "materiau_phong" )
		{
			_materiau = new MateriauPhong(_textureAmbiant, _textureDiffus, _textureSpeculaire, _textureNs);
			_scene.enregistrerMateriau(_materiau);
			_materiau->_nom = _nom;
			return true;
		}
		if( qName == "materiau_miroir" )
		{
			_materiau = new MateriauMiroir(_textureAmbiant, _textureDiffus, _textureSpeculaire, _textureNs, _textureMiroir);
			_scene.enregistrerMateriau(_materiau);
			_materiau->_nom = _nom;
			return true;
		}
		if( qName == "primitive_triangle" )
		{
			Primitive *primitive = new PrimitiveTriangle(_materiau, _sommets[0], _sommets[1], _sommets[2]);
			_scene.enregistrerPrimitive(primitive);
			return true;
		}
		return true;
	}
};

Loader::Loader(int argc, char **argv, const char *fichierXsd):
		_application(argc, argv), _fichierXsd(fichierXsd)
{}

bool Loader::validerFichier(const String &nomFichierComplet) const
{
	// charge le schema XML
	QUrl urlSchema = QUrl::fromLocalFile(_fichierXsd.c_str());
	QXmlSchema schema;
	if (!schema.load(urlSchema))
	{
		std::cerr << "Loader::validerFichier : schema XML invalide.\n";
		return false;
	}

	// charge le fichier XML
	QFile fichier(nomFichierComplet.toC());
	fichier.open(QIODevice::ReadOnly);
	QUrl urlFichier = QUrl::fromLocalFile(nomFichierComplet.toC());

	// effectue la validation
	QXmlSchemaValidator validator(schema);
	return validator.validate(&fichier, urlFichier);
}

bool Loader::chargerScene(const String &chemin, const String &nomFichier, Scene &scene)
{
	// charge et valide le fichier
	String nomComplet = chemin + nomFichier;
	if (!validerFichier(nomComplet))
	{
		std::cerr << "Loader::chargerScene : fichier XML invalide.\n";
		return false;
	}

	// instancie le parser
	Handler handler(scene, chemin);
	QFile fichier(nomComplet.toC());
	QXmlInputSource source(&fichier);
	QXmlSimpleReader reader;
	reader.setContentHandler(&handler);
	reader.setErrorHandler(&handler);

	// lance le parsing
	if (!reader.parse(source))
	{
		std::cerr << "Loader::chargerScene : erreur lors du parsing XML.\n";
		return false;
	}

	return true;
}

