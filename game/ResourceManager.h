template < typename T >
class ResourceManager
{
public:
	static T* GetInstance();
	static void DestroyInstance();

	template <typename... Args>
	static T *Load(WCHAR* &filename, Args&&... args)
	{

		// looks in the map to see if the
		// resource is already loaded

		std::unordered_map<WCHAR *, T* >::iterator it = Map.find(filename);

		if (it != Map.end())
		{
			std::unordered_map<WCHAR *, UINT>::iterator iter = Reference.find(filename);
			iter->second++;
			return it->second;
		}

		// if we get here the resource must be loaded
		// allocate new resource using the raii paradigm
		// you must supply the class with a proper constructor
		// see header for details

		T *resource = new T(filename, std::forward<Args>(args)...);

		// increase references , this sets the references count to 1
		Reference.insert(std::pair<WCHAR *, UINT>(filename, 1));

		// insert into the map
		Map.insert(std::pair< WCHAR*, T* >(filename, resource));
		return resource;
	}

	template <typename... Args>
	static T *Load(const WCHAR* file, Args&&... args)
	{
		// looks in the map to see if the
		// resource is already loaded

		WCHAR *filename = const_cast<WCHAR*>(file);
		std::unordered_map<WCHAR *, T* >::iterator it = Map.find(filename);

		if (it != Map.end())
		{
			std::unordered_map<WCHAR *, UINT>::iterator iter = Reference.find(filename);
			iter->second++;
			return it->second;
		}

		// if we get here the resource must be loaded
		// allocate new resource using the raii paradigm
		// you must supply the class with a proper constructor
		// see header for details

		T *resource = new T(filename, std::forward<Args>(args)...);

		// increase references , this sets the references count to 1
		Reference.insert(std::pair<WCHAR *, UINT>(filename, 1));

		// insert into the map
		Map.insert(std::pair< WCHAR*, T* >(filename, resource));
		return resource;
	}

	static bool Unload(const WCHAR *file)
	{
		// normalize it

		// find the item to delete
		WCHAR *filename = const_cast<WCHAR*>(file);
		std::unordered_map< WCHAR*, T* >::iterator it = Map.find(filename);

		if (it != Map.end())
		{

			// decrease references

			it->second--;

			// if item has 0 references, means
			// the item isn't more used so , 
			// delete from main  database

			if (it->second == 0)
			{
				// call the destructor 
				delete(it->second);
				Map.erase(it);
			}

			return true;

		}
		return false;
	}

	static const int Size()
	{
		return Map.size();
	}

private:
	static T* mInstance;

	ResourceManager(ResourceManager const&) { };
	ResourceManager &operator = (ResourceManager const&) {}

	static std::unordered_map<WCHAR *, T* > Map;
	static std::unordered_map<WCHAR *, UINT> Reference;
	static void ReleaseAll()
	{
		std::unordered_map< WCHAR*, T* >::iterator it = Map.begin();

		while (it != Map.end())
		{
			delete it->second;
			it = Map.erase(it);
		}
	}

protected:
	ResourceManager()
	{
		mInstance = static_cast<T*>(this);
	}
	~ResourceManager()
	{
		ReleaseAll();
	}
};

template<typename T>
typename T* ResourceManager<T>::mInstance = nullptr;

template<typename T>
std::unordered_map<WCHAR *, T* > ResourceManager<T>::Map;

template<typename T>
std::unordered_map<WCHAR *, UINT> ResourceManager<T>::Reference;

template<typename T>
T * ResourceManager<T>::GetInstance()
{
	if (mInstance == nullptr)
		mInstance = new T;

	return mInstance;
}

template<typename T>
void ResourceManager<T>::DestroyInstance()
{
	if (mInstance != nullptr)
		delete mInstance;
	mInstance = nullptr;
}
