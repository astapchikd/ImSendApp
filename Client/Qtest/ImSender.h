// This file is generated by omniidl (C++ backend)- omniORB_4_3. Do not edit.
#ifndef __ImSender_hh__
#define __ImSender_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif






#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif



_CORBA_MODULE ImageSender

_CORBA_MODULE_BEG

#ifndef __ImageSender_mSender__
#define __ImageSender_mSender__
  class Sender;
  class _objref_Sender;
  class _impl_Sender;
  
  typedef _objref_Sender* Sender_ptr;
  typedef Sender_ptr SenderRef;

  class Sender_Helper {
  public:
    typedef Sender_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_Sender, Sender_Helper> Sender_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_Sender,Sender_Helper > Sender_out;

#endif

  // interface Sender
  class Sender {
  public:
    // Declarations for this interface type.
    typedef Sender_ptr _ptr_type;
    typedef Sender_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static inline _ptr_type _fromObjRef(omniObjRef* o) {
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    class image_var;

    class image : public _CORBA_Unbounded_Sequence_Char {
    public:
      typedef image_var _var_type;
      inline image() {}
      inline image(const image& _s)
        : _CORBA_Unbounded_Sequence_Char(_s) {}

      inline image(_CORBA_ULong _max)
        : _CORBA_Unbounded_Sequence_Char(_max) {}
      inline image(_CORBA_ULong _max, _CORBA_ULong _len, ::CORBA::Char* _val, _CORBA_Boolean _rel=0)
        : _CORBA_Unbounded_Sequence_Char(_max, _len, _val, _rel) {}

    

      inline image& operator = (const image& _s) {
        _CORBA_Unbounded_Sequence_Char::operator=(_s);
        return *this;
      }
    };

    class image_out;

    class image_var {
    public:
      inline image_var() : _pd_seq(0) {}
      inline image_var(image* _s) : _pd_seq(_s) {}
      inline image_var(const image_var& _s) {
        if (_s._pd_seq)  _pd_seq = new image(*_s._pd_seq);
        else             _pd_seq = 0;
      }
      inline ~image_var() { if (_pd_seq)  delete _pd_seq; }
        
      inline image_var& operator = (image* _s) {
        if (_pd_seq)  delete _pd_seq;
        _pd_seq = _s;
        return *this;
      }
      inline image_var& operator = (const image_var& _s) {
        if (&_s != this) {
          if (_s._pd_seq) {
            if (!_pd_seq)  _pd_seq = new image;
            *_pd_seq = *_s._pd_seq;
          }
          else if (_pd_seq) {
            delete _pd_seq;
            _pd_seq = 0;
          }
        }
        return *this;
      }
      inline ::CORBA::Char& operator [] (_CORBA_ULong _s) {
        return (*_pd_seq)[_s];
      }

    

      inline image* operator -> () { return _pd_seq; }
      inline const image* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
      inline operator image& () const { return *_pd_seq; }
#else
      inline operator const image& () const { return *_pd_seq; }
      inline operator image& () { return *_pd_seq; }
#endif
        
      inline const image& in() const { return *_pd_seq; }
      inline image&       inout()    { return *_pd_seq; }
      inline image*&      out() {
        if (_pd_seq) { delete _pd_seq; _pd_seq = 0; }
        return _pd_seq;
      }
      inline image* _retn() { image* tmp = _pd_seq; _pd_seq = 0; return tmp; }
        
      friend class image_out;
      
    private:
      image* _pd_seq;
    };

    class image_out {
    public:
      inline image_out(image*& _s) : _data(_s) { _data = 0; }
      inline image_out(image_var& _s)
        : _data(_s._pd_seq) { _s = (image*) 0; }
      inline image_out(const image_out& _s) : _data(_s._data) {}
      inline image_out& operator = (const image_out& _s) {
        _data = _s._data;
        return *this;
      }
      inline image_out& operator = (image* _s) {
        _data = _s;
        return *this;
      }
      inline operator image*&()  { return _data; }
      inline image*& ptr()       { return _data; }
      inline image* operator->() { return _data; }

      inline ::CORBA::Char& operator [] (_CORBA_ULong _i) {
        return (*_data)[_i];
      }

    

      image*& _data;

    private:
      image_out();
      image_out& operator=(const image_var&);
    };

  
  };

  class _objref_Sender :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    // IDL operations
    ::CORBA::Boolean Send(const char* filename, ::CORBA::Long sizefname, const ::ImageSender::Sender::image& im);
    ::CORBA::Boolean shutdown();

    // Constructors
    inline _objref_Sender()  { _PR_setobj(0); }  // nil
    _objref_Sender(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_Sender();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_Sender(const _objref_Sender&);
    _objref_Sender& operator = (const _objref_Sender&);
    // not implemented

    friend class Sender;
  };

  class _pof_Sender : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_Sender() : _OMNI_NS(proxyObjectFactory)(Sender::_PD_repoId) {}
    virtual ~_pof_Sender();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_Sender :
    public virtual omniServant
  {
  public:
    virtual ~_impl_Sender();

    virtual ::CORBA::Boolean Send(const char* filename, ::CORBA::Long sizefname, const ::ImageSender::Sender::image& im) = 0;
    virtual ::CORBA::Boolean shutdown() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_ImageSender
_CORBA_MODULE_BEG

  class Sender :
    public virtual ImageSender::_impl_Sender,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~Sender();

    inline ::ImageSender::Sender_ptr _this() {
      return (::ImageSender::Sender_ptr) _do_this(::ImageSender::Sender::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_ImageSender
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr



inline void
ImageSender::Sender::_marshalObjRef(::ImageSender::Sender_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_ImSender
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_ImSender
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_ImSender
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_ImSender
#endif

#endif  // __ImSender_hh__

