template< class ClassT >
void Helium::Reflect::Class::Create( Class const*& pointer, const tchar_t* name, const tchar_t* baseName, CreateObjectFunc creator )
{
	Class* type = Class::Create();
	pointer = type;

	// populate reflection information
	Composite::Create< ClassT >( name, baseName, &ClassT::PopulateComposite, type );

	// setup factory function
	type->m_Creator = creator;

	// fetch a potential default instance from the composite
	ClassT* instance = static_cast< ClassT* >( type->Composite::m_Default );
	if ( instance )
	{
		type->m_Default = instance;
	}
	else
	{
		// create the default instance
		if ( pointer->m_Creator )
		{
			type->Composite::m_Default = type->m_Default = type->m_Creator();
		}
	}
}

template< class ClassT, class BaseT >
Helium::Reflect::ObjectRegistrar< ClassT, BaseT >::ObjectRegistrar(const tchar_t* name)
	: TypeRegistrar( name )
{
	HELIUM_ASSERT( ClassT::s_Class == NULL );
	TypeRegistrar::AddToList( RegistrarTypes::Object, this );
}

template< class ClassT, class BaseT >
Helium::Reflect::ObjectRegistrar< ClassT, BaseT >::~ObjectRegistrar()
{
	Unregister();
	TypeRegistrar::RemoveFromList( RegistrarTypes::Object, this );
}

template< class ClassT, class BaseT >
void Helium::Reflect::ObjectRegistrar< ClassT, BaseT >::Register()
{
	if ( ClassT::s_Class == NULL )
	{
		BaseT::s_Registrar.Register();
		AddTypeToRegistry( ClassT::CreateClass() );
	}
}

template< class ClassT, class BaseT >
void Helium::Reflect::ObjectRegistrar< ClassT, BaseT >::Unregister()
{
	if ( ClassT::s_Class != NULL )
	{
		RemoveTypeFromRegistry( ClassT::s_Class );
		ClassT::s_Class = NULL;
	}
}

template< class ClassT >
Helium::Reflect::ObjectRegistrar< ClassT, void >::ObjectRegistrar(const tchar_t* name)
	: TypeRegistrar( name )
{
	HELIUM_ASSERT( ClassT::s_Class == NULL );
	TypeRegistrar::AddToList( RegistrarTypes::Object, this );
}

template< class ClassT >
Helium::Reflect::ObjectRegistrar< ClassT, void >::~ObjectRegistrar()
{
	Unregister();
	TypeRegistrar::RemoveFromList( RegistrarTypes::Object, this );
}

template< class ClassT >
void Helium::Reflect::ObjectRegistrar< ClassT, void >::Register()
{
	if ( ClassT::s_Class == NULL )
	{
		AddTypeToRegistry( ClassT::CreateClass() );
	}
}

template< class ClassT >
void Helium::Reflect::ObjectRegistrar< ClassT, void >::Unregister()
{
	if ( ClassT::s_Class != NULL )
	{
		RemoveTypeFromRegistry( ClassT::s_Class );
		ClassT::s_Class = NULL;
	}
}