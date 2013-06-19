#ifndef COIN_CORE_MANAGED_H
#define COIN_CORE_MANAGED_H

/* this class, CManaged, keeps track of all references and deletes itself when no more
	references exist.  Note that the user must assign pointers to the class by use of
	strong and weak pointers.  Strong pointers must be deleted before the managed class can
	be deleted and all weak pointers will be deleted at the time the managed class is
	deleted.

	To create a managed object the implementer must create it through the pointer class

	example:

	SPtr< CManaged > m_pManaged = new CManaged();// creates a strong pointer
	
	WPtr< CManaged > m_pManaged = new CManaged();// creates a weak pointer

	a pointer will automatically delete itself when it goes out of scope,
	is set to NULL, or is manually deleted.

	if an object no longer has any stong pointers pointing to it it will delete
	itself and set all weak pointers to NULL

*/

#include "core\memory.h"

// many features of the pointers are not used in final to slightly improve performance
// none smart pointers will be basically no more than a typical pointer
#define SMART_POINTER  ( DEBUG || RELEASE )

// forward declare
class CPtrBase;

// the proxy is templated so this is needed for use by other classes
class CProxyBase 
{
public:
    CProxyBase() {;}
    virtual ~CProxyBase() {;}
	virtual void vPrintRef() = 0;
};


// proxies sit infront of an object and keep track of how many pointers are pointing to that object
// and where those pointers are in memory.  Every object has exacly one proxy which handles most of
// smart pointer error checking.

// T must be derived from CManaged
template <class T> 
class CProxy : public CProxyBase {
public:
    CProxy() 
	: m_ptr( NULL ),
	  m_cStrong( 0 ),
	  m_cWeak( 0 ),
	  m_pRefStrong( NULL ),
	  m_pRefWeak( NULL )
	{ 
    }

    CProxy( T * p_ptr ) 
	: m_ptr( p_ptr ),
	  m_cStrong( 0 ),
	  m_cWeak( 0 ),
	  m_pRefStrong( NULL ),
	  m_pRefWeak( NULL )
	{ 
    }

    virtual ~CProxy() 
	{
		ASSERT( m_cStrong == 0 );
		vRemoveAllWeak();        
		if ( m_ptr ) 
		{
            m_ptr->vSetProxy( NULL );
        }
        m_ptr = NULL; 
    }

    operator T*() const 
	{
        return m_ptr; 
    }

    T& operator*() const 
	{
        ASSERT( m_ptr ); 
        return *m_ptr; 
    }

    T* operator->() const 
	{
        ASSERT( m_ptr ); 
        return m_ptr; 
    }

	T * pGet()
	{
		return m_ptr;
	}

    void vAddStrong( CPtrBase * p_ptr = NULL ) 
	{ 
#if SMART_POINTER
       	if( p_ptr )
		{
			SRef * t_pRef = new SRef();
			if( m_pRefStrong )
			{
				t_pRef->m_pNext = m_pRefStrong;
				m_pRefStrong->m_pPrev = t_pRef;
			}
			t_pRef->m_pPrev = NULL;
			m_pRefStrong = t_pRef;
			m_pRefStrong->m_ptr = p_ptr;
		}
#endif
		++m_cStrong;
    }

    void vAddWeak( CPtrBase * p_ptr ) 
	{ 
       ASSERT( p_ptr );

		SRef * t_pRef = new SRef();
		if( m_pRefWeak )
		{
			t_pRef->m_pNext = m_pRefWeak;
			m_pRefWeak->m_pPrev = t_pRef;
		}
		t_pRef->m_pPrev = NULL;
		m_pRefWeak = t_pRef;
		m_pRefWeak->m_ptr = p_ptr;
		
		++m_cWeak;
    }

	void vRemoveStrong( CPtrBase * p_ptr = NULL ) 
	{ 
#if SMART_POINTER
        if( p_ptr )
		{
			if( p_ptr == m_pRefStrong->m_ptr )
			{
				if( m_pRefStrong->m_pNext )
				{
					m_pRefStrong->m_pNext->m_pPrev = NULL;
					m_pRefStrong = m_pRefStrong->m_pNext;
				}
				else
				{
					m_pRefStrong = NULL;
				}
			}
			else
			{
				for( SRef * t_pRef = m_pRefStrong->m_pNext; t_pRef; t_pRef = t_pRef->m_pNext )
				{
					if( t_pRef->m_ptr == p_ptr )
					{
						if( t_pRef->m_pPrev )
						{
							t_pRef->m_pPrev->m_pNext = t_pRef->m_pNext;
						}
						if( t_pRef->m_pNext )
						{
							t_pRef->m_pNext->m_pPrev = t_pRef->m_pPrev;
						}
						delete t_pRef;
						break;
					}
				}
			}
			//ASSERT_MSG( false, "Unable to find and remove weak pointer 0x%x\n", *p_ptr)
		}
#endif

		if( --m_cStrong <= 0 )
		{
			delete m_ptr;
		}
    }

	void vRemoveWeak( CPtrBase * p_ptr ) 
	{ 
		ASSERT( p_ptr );
		
		if( m_cWeak == 0 )
		{
			return;
		}

		if( p_ptr == m_pRefWeak->m_ptr )
		{
			if( m_pRefWeak->m_pNext )
			{
				m_pRefWeak->m_pNext->m_pPrev = NULL;
				m_pRefWeak = m_pRefWeak->m_pNext;
			}
			else
			{
				m_pRefWeak = NULL;
			}
			--m_cWeak;
			return;
		}
		for( SRef * t_pRef = m_pRefWeak->m_pNext; t_pRef; t_pRef = t_pRef->m_pNext )
		{
			if( t_pRef->m_ptr == p_ptr )
			{
				if( t_pRef->m_pPrev )
				{
					t_pRef->m_pPrev->m_pNext = t_pRef->m_pNext;
				}
				if( t_pRef->m_pNext )
				{
					t_pRef->m_pNext->m_pPrev = t_pRef->m_pPrev;
				}
				delete t_pRef;
				--m_cWeak;
				return;
			}
		}
		ASSERT_MSG( false, L"Unable to find and remove weak pointer 0x%x\n", *p_ptr)
    }

	virtual void vPrintRef()
	{
		DEBUG_PRINT( L"%u weak pointers\n", m_cWeak );
		DEBUG_PRINT( L"Printing Weak Pointers\n" );
		for( SRef * t_pRef = m_pRefWeak; t_pRef; t_pRef = t_pRef->m_pNext )
		{
			DEBUG_PRINT( L"\t0x%x,\n", *t_pRef );
		}

		DEBUG_PRINT( L"%u strong pointers\n", m_cStrong );
#if SMART_POINTER
		DEBUG_PRINT( L"Printing Strong Pointers\n" );
		for( SRef * t_pRef = m_pRefStrong; t_pRef; t_pRef = t_pRef->m_pNext )
		{
			DEBUG_PRINT( L"\t0x%x,\n", *t_pRef );
		}
#endif
	}


protected:

	void vRemoveAllWeak()
	{
		SRef * t_pRefNext = NULL;
		for( SRef * t_pRef = m_pRefWeak; t_pRef; t_pRef = t_pRefNext )
		{
			t_pRefNext = t_pRef->m_pNext;
			t_pRef->m_ptr = NULL;
			delete t_pRef;
			--m_cWeak;
		}
		if( t_pRefNext )
		{
			delete t_pRefNext;
		}
		ASSERT( m_cWeak == 0 );
	}

	// keep track of references in a linked list style
	struct SRef
	{
		SRef()
		: m_pNext( NULL ),
		  m_pPrev( NULL ),
		  m_ptr( NULL )
		{ ; }

		SRef * m_pNext;
		SRef * m_pPrev;

		CPtrBase * m_ptr;
	};

	SRef *	m_pRefWeak;
	// no reason to track strong pointers except when debugging
#if SMART_POINTER
	SRef *	m_pRefStrong;
#endif

    T *		m_ptr;
    u32		m_cStrong;
	u32		m_cWeak;

private:
	// proxies cannot be set equal to each other, that means the object has been
	// destroyed and recreated without the proxy or any smart pointers knowing
    CProxy< T >& operator=( CProxy< T >& p_p );
    CProxy( const CProxy< T >& p_p);
};

class CPtrBase
{
public:
	CPtrBase(){;}
	virtual ~CPtrBase(){;}
};

template< class T > 
class WPtr;

// this contains the smart pointers
#if SMART_POINTER

// T must be derived from CManaged
template< class T > 
class SPtr: public CPtrBase
{
public:
    SPtr() 
	: m_pProxy(NULL) 
	{;}

    SPtr( T * p_ptr ) 
	{
        if ( p_ptr == NULL ) {
            m_pProxy = NULL;
            return;
        }
        if ( p_ptr->pProxy() == NULL ) {
            //this is the first pointer to access
            //the object so it must create its proxy
            p_ptr->vSetProxy( new CProxy< T >( p_ptr ) );
        }
        m_pProxy = reinterpret_cast< CProxy< T > * >( p_ptr->pProxy() );
        m_pProxy->vAddStrong( this ); 
    }

    SPtr( const SPtr< T >& p_ptr ) 
	{
        m_pProxy = p_ptr.m_pProxy;
        if( m_pProxy != NULL ) 
		{
            m_pProxy->vAddStrong( this );
        }
    }

	SPtr( const WPtr< T >& p_ptr ) 
	{
        m_pProxy = p_ptr.m_pProxy;
        if( m_pProxy != NULL ) 
		{
            m_pProxy->vAddStrong( this );
        }
    }

    virtual ~SPtr() 
	{ 
        if( m_pProxy ) 
		{
            m_pProxy->vRemoveStrong( this ); 
        }
    }

    operator T*() const 
	{
        return m_pProxy->operator T*();
    }

    T& operator*() const 
	{ 
        return m_pProxy->operator*(); 
    }

    T* operator->() const 
	{ 
        return m_pProxy->operator->(); 
    }

    virtual SPtr< T >& operator=( SPtr< T > &p_ptr) 
	{ 
        return operator=( ( T * )p_ptr ); 
    }

    virtual SPtr< T >& operator=( T * p_ptr ) 
	{
        if ( m_pProxy ) 
		{
            m_pProxy->vRemoveStrong( this );
        }

        if ( p_ptr == NULL ) 
		{
            m_pProxy = NULL;
        }
        else 
		{
            if ( p_ptr->pProxy() == NULL) 
			{
                p_ptr->vSetProxy( new CProxy< T >( p_ptr ) );
            }
            m_pProxy = ( CProxy< T > * )( p_ptr->pProxy() );
            m_pProxy->vAddStrong( this );
        }
        return *this; 
    }

    CProxy< T > * pProxy() const
	{ 
        return m_pProxy;
    }
	
	T * pGet() const
	{ 
        return m_pProxy->pGet();
    }

protected:
    CProxy< T > * m_pProxy;
};


template< class T > 
class WPtr: public CPtrBase
{
public:
    WPtr() 
	: m_pProxy(NULL) 
	{;}

    WPtr( T * p_ptr ) 
	{
        if ( p_ptr == NULL ) {
            m_pProxy = NULL;
            return;
        }
        if ( p_ptr->pProxy() == NULL ) {
            //this is the first pointer to access
            //the object so it must create its proxy
            p_ptr->vSetProxy( new CProxy< T >( p_ptr ) );
        }
        m_pProxy = reinterpret_cast< CProxy< T > * >( p_ptr->pProxy() );
        m_pProxy->vAddWeak( this ); 
    }

    WPtr( const WPtr< T >& p_ptr ) 
	{
        m_pProxy = p_ptr.m_pProxy;
        if( m_pProxy != NULL ) 
		{
            m_pProxy->vAddWeak( this );
        }
    }

	WPtr( const SPtr< T >& p_ptr ) 
	{
        m_pProxy = p_ptr.m_pProxy;
        if( m_pProxy != NULL ) 
		{
            m_pProxy->vAddWeak( this );
        }
    }

    virtual ~WPtr() 
	{ 
        if( m_pProxy ) 
		{
            m_pProxy->vRemoveWeak( this ); 
        }
    }

    operator T*() const 
	{
        return m_pProxy->operator T*();
    }

    T& operator*() const 
	{ 
        return m_pProxy->operator*(); 
    }

    T* operator->() const 
	{ 
        return m_pProxy->operator->(); 
    }

    virtual WPtr< T >& operator=( WPtr< T > &p_ptr) 
	{ 
        return operator=( ( T * )p_ptr ); 
    }

    virtual WPtr< T >& operator=( T * p_ptr ) 
	{
        if ( m_pProxy ) 
		{
            m_pProxy->vRemoveWeak( this );
        }

        if ( p_ptr == NULL ) 
		{
            m_pProxy = NULL;
        }
        else 
		{
            if ( p_ptr->pProxy() == NULL) 
			{
                p_ptr->vSetProxy( new CProxy< T >( p_ptr ) );
            }
            m_pProxy = ( CProxy< T > * )( p_ptr->pProxy() );
            m_pProxy->vAddWeak( this );
        }
        return *this; 
    }

    CProxy< T > * pProxy() const
	{ 
        return m_pProxy;
    }

	T * pGet() const
	{ 
        return m_pProxy->pGet();
    }

protected:
    CProxy< T > * m_pProxy;
};


#else // not using smart pointers

template < class T > 
class SPtr: CPtrBase
{
public:
    SPtr() 
	: m_ptr( NULL ) 
	{;}

    SPtr( T * p_ptr ) 
	: m_ptr( p_ptr ) 
	{;}

    virtual ~SPtr() {}

    operator T*() const 
	{
        return m_ptr;
    }

    T& operator*() const 
	{ 
        return *m_ptr;
    }

    T* operator->() const 
	{ 
        return m_ptr;
    }

    virtual SPtr< T >& operator=( SPtr< T > &p_ptr ) 
	{ 
        m_ptr = p_ptr;
        return *this; 
    }

	virtual SPtr< T >& operator=( WPtr< T > &p_ptr ) 
	{ 
        m_ptr = p_ptr;
        return *this; 
    }

    virtual SPtr< T >& operator=( T* p_ptr ) 
	{
        m_ptr = p_ptr;
        return *this; 
    }

    T * pGet() const
	{ 
        return m_pProxy->pGet();
    }

protected:
    T * m_ptr;
};

template < class T > 
class WPtr: CPtrBase
{
public:
    WPtr() 
	: m_ptr( NULL ) 
	{;}

    WPtr( T * p_ptr ) 
	: m_ptr( p_ptr ) 
	{;}

    virtual ~WPtr() {}

    operator T*() const 
	{
        return m_ptr;
    }

    T& operator*() const 
	{ 
        return *m_ptr;
    }

    T* operator->() const 
	{ 
        return m_ptr;
    }

    virtual WPtr< T >& operator=( WPtr< T > &p_ptr ) 
	{ 
        m_ptr = p_ptr;
        return *this; 
    }

	virtual WPtr< T >& operator=( SPtr< T > &p_ptr ) 
	{ 
        m_ptr = p_ptr;
        return *this; 
    }

    virtual WPtr< T >& operator=( T* p_ptr ) 
	{
        m_ptr = p_ptr;
        return *this; 
    }

    T * pGet() const
	{ 
        return m_ptr;
    }

protected:
    T * m_ptr;
};


#endif

class CManaged {
public:
    CManaged() 
	: m_pProxy( NULL )
	{;}

    CManaged( const CManaged& p_p ) 
	: m_pProxy( NULL )
	{;}

    ~CManaged() 
	{ 
        if ( m_pProxy ) 
		{           
			delete m_pProxy; 
            m_pProxy = NULL; 
        }
    }

    CManaged& operator=( const CManaged& p_p ) 
	{
		// we don't want to copy anything so this new object has its own proxy
        return *this; 
    }


    CProxyBase * pProxy() const {
        return m_pProxy;
    }

    void vSetProxy( CProxyBase * p_pProxy ) 
	{
        ASSERT_MSG( !m_pProxy || !p_pProxy, L"Object can only have one proxy" );
        m_pProxy = p_pProxy;
    }

	void vPrintRef()
	{
#if SMART_POINTER
		ASSERT( m_pProxy );
		m_pProxy->vPrintRef();
#endif
	}

protected:

    CProxyBase * m_pProxy;

};

#endif // coin_core_managed_h
