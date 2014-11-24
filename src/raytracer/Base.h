#ifndef BASE_H_
#define BASE_H_

#include <string>

/// \brief Chaine de caracteres.
///
class String : public std::string
{
public:
	/// \brief Constructeur par defaut.
	///
	String(): std::string() {}

	/// \brief Constructeur.
	///
	String(const std::string &str): std::string(str) {}

	/// \brief Constructeur par recopie.
	///
	String(const String &str): std::string(str) {}

	/// \brief Constructeur.
	///
	String(const char *c_str): std::string(c_str) {}

	/// \brief Retourne une chaine de caratere style C.
	///
	const char* toC() const {return c_str();}
};

/// \brief Flottant.
///
typedef double reel;

/// \brief Interpolation linéaire générique.
///
template <typename T>
T interpoler(const T& P0, const T& P1, reel t)
{
	return P0*(1-t) + P1*t;
}

#include <set>

/// \brief Ensemble de pointeurs d'objet.
///
/// Les objets pointes sont detruits automatiquement. Les pointeurs sont uniques.
///
template <typename T>
class AutoSet : public std::set<T*>
{
public:
	/// \brief Iterateur sur l'ensemble.
	///
	typedef typename std::set<T*>::const_iterator const_iterator;

	/// \brief Ajoute un element dans l'ensemble
	///
	void ajouter(T* element)
	{
		this->insert(element);
	}

	/// \brief Detruit l'ensemble ainsi que les objets pointes.
	///
	~AutoSet()
	{
		for (const_iterator it=this->begin(); it!=this->end(); ++it)
		{
			delete *it;
		}
	}
};

#include <map>

/// \brief Dictionnaire de pointeurs d'objet.
///
/// Les objets pointes sont detruits automatiquement.
///
template <typename T>
class AutoMap : public std::map<String, T*>
{
public:
	/// \brief Iterateur sur le dictionnaire.
	///
	typedef typename std::map<String, T*>::const_iterator const_iterator;

	/// \brief Trouve une entree dans le dictionnaire.
	///
	/// Retourne le pointeur vers l'objet ou 0 si l'entree n'est pas dans le dictionnaire.
	///
	T* trouver(const String &key)
	{
		const_iterator it = this->find(key);

		if (it == this->end())
		{
			return 0;
		}
		else
		{
			return (*it).second;
		}
	}

	/// \brief Ajoute une entree dans le dictionnaire.
	///
	/// Si l'entree est deja presente, celle-ci est remplacee sans etre detruite.
	///
	void ajouter(const String &key, T* element)
	{
		this->operator[](key) = element;
	}

	/// \brief Detruit le dictionnaire ainsi que les objets pointes.
	///
	~AutoMap()
	{
		for (const_iterator it=this->begin(); it!=this->end(); ++it)
		{
			std::pair<String, T*> p = *it;
			delete p.second;
		}
	}
};

#endif


