//
// Generated file, do not edit! Created by opp_msgc 3.4 from HChordMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HChordMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw new cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}
template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw new cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

// Automatically supply array (un)packing functions
template<typename T>
void doPacking(cCommBuffer *b, T *t, int n) {
    for (int i=0; i<n; i++)
        doPacking(b,t[i]);
}
template<typename T>
void doUnpacking(cCommBuffer *b, T *t, int n) {
    for (int i=0; i<n; i++)
        doUnpacking(b,t[i]);
}
inline void doPacking(cCommBuffer *, cPolymorphic&) {}
inline void doUnpacking(cCommBuffer *, cPolymorphic&) {}

#define DOPACKING(T,R) \
    inline void doPacking(cCommBuffer *b, T R a) {b->pack(a);}  \
    inline void doPacking(cCommBuffer *b, T *a, int n) {b->pack(a,n);}  \
    inline void doUnpacking(cCommBuffer *b, T& a) {b->unpack(a);}  \
    inline void doUnpacking(cCommBuffer *b, T *a, int n) {b->unpack(a,n);}
#define _
DOPACKING(char,_)
DOPACKING(unsigned char,_)
DOPACKING(bool,_)
DOPACKING(short,_)
DOPACKING(unsigned short,_)
DOPACKING(int,_)
DOPACKING(unsigned int,_)
DOPACKING(long,_)
DOPACKING(unsigned long,_)
DOPACKING(float,_)
DOPACKING(double,_)
DOPACKING(long double,_)
DOPACKING(char *,_)
DOPACKING(const char *,_)
DOPACKING(opp_string,&)
//DOPACKING(std::string,&)
#undef _
#undef DOPACKING


Register_Class(HChordMessage);

HChordMessage::HChordMessage(const char *name, int kind) : BaseOverlayMessage(name,kind)
{
    this->mesg_type_var = 0;
}

HChordMessage::HChordMessage(const HChordMessage& other) : BaseOverlayMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HChordMessage::~HChordMessage()
{
    unsigned int i;
}

HChordMessage& HChordMessage::operator=(const HChordMessage& other)
{
    if (this==&other) return *this;
    unsigned int i;
    BaseOverlayMessage::operator=(other);
    this->src_var = other.src_var;
    this->dest_var = other.dest_var;
    this->mesg_type_var = other.mesg_type_var;
    return *this;
}

void HChordMessage::netPack(cCommBuffer *b)
{
    BaseOverlayMessage::netPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->dest_var);
    doPacking(b,this->mesg_type_var);
}

void HChordMessage::netUnpack(cCommBuffer *b)
{
    BaseOverlayMessage::netUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dest_var);
    doUnpacking(b,this->mesg_type_var);
}

NodeHandle& HChordMessage::getSrc()
{
    return src_var;
}

void HChordMessage::setSrc(const NodeHandle& src_var)
{
    this->src_var = src_var;
}

NodeHandle& HChordMessage::getDest()
{
    return dest_var;
}

void HChordMessage::setDest(const NodeHandle& dest_var)
{
    this->dest_var = dest_var;
}

int HChordMessage::getMesg_type() const
{
    return mesg_type_var;
}

void HChordMessage::setMesg_type(int mesg_type_var)
{
    this->mesg_type_var = mesg_type_var;
}

class HChordMessageDescriptor : public cClassDescriptor
{
  public:
    HChordMessageDescriptor();
    virtual ~HChordMessageDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HChordMessageDescriptor);

HChordMessageDescriptor::HChordMessageDescriptor() : cClassDescriptor("HChordMessage", "BaseOverlayMessage")
{
}

HChordMessageDescriptor::~HChordMessageDescriptor()
{
}

bool HChordMessageDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HChordMessage *>(obj)!=NULL;
}

const char *HChordMessageDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HChordMessageDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int HChordMessageDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        case 1: return FD_ISCOMPOUND;
        case 2: return FD_ISEDITABLE;
        default: return 0;
    }
}

const char *HChordMessageDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "src";
        case 1: return "dest";
        case 2: return "mesg_type";
        default: return NULL;
    }
}

const char *HChordMessageDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        case 2: return "int";
        default: return NULL;
    }
}

const char *HChordMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HChordMessageDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HChordMessage *pp _MAYBEUNUSED = (HChordMessage *)object;
    switch (field) {
        default: return 0;
    }
}

bool HChordMessageDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HChordMessage *pp _MAYBEUNUSED = (HChordMessage *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getDest(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 2: long2string(pp->getMesg_type(),resultbuf,bufsize); return true;
        default: return false;
    }
}

bool HChordMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HChordMessage *pp _MAYBEUNUSED = (HChordMessage *)object;
    switch (field) {
        case 2: pp->setMesg_type(string2long(value)); return true;
        default: return false;
    }
}

const char *HChordMessageDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HChordMessageDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HChordMessage *pp _MAYBEUNUSED = (HChordMessage *)object;
    switch (field) {
        case 0: return (void *)(&pp->getSrc()); break;
        case 1: return (void *)(&pp->getDest()); break;
        default: return NULL;
    }
}

Register_Class(HJoinCall);

HJoinCall::HJoinCall(const char *name, int kind) : HChordMessage(name,kind)
{
}

HJoinCall::HJoinCall(const HJoinCall& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HJoinCall::~HJoinCall()
{
    unsigned int i;
}

HJoinCall& HJoinCall::operator=(const HJoinCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HJoinCall::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HJoinCall::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HJoinCallDescriptor : public cClassDescriptor
{
  public:
    HJoinCallDescriptor();
    virtual ~HJoinCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HJoinCallDescriptor);

HJoinCallDescriptor::HJoinCallDescriptor() : cClassDescriptor("HJoinCall", "HChordMessage")
{
}

HJoinCallDescriptor::~HJoinCallDescriptor()
{
}

bool HJoinCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HJoinCall *>(obj)!=NULL;
}

const char *HJoinCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HJoinCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HJoinCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HJoinCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HJoinCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HJoinCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HJoinCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HJoinCall *pp _MAYBEUNUSED = (HJoinCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool HJoinCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HJoinCall *pp _MAYBEUNUSED = (HJoinCall *)object;
    switch (field) {
        default: return false;
    }
}

bool HJoinCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HJoinCall *pp _MAYBEUNUSED = (HJoinCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *HJoinCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HJoinCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HJoinCall *pp _MAYBEUNUSED = (HJoinCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HJoinResponse);

HJoinResponse::HJoinResponse(const char *name, int kind) : HChordMessage(name,kind)
{
    unsigned int i;
    this->sucNum_var = 0;
    sucNode_arraysize = 0;
    this->sucNode_var = 0;
}

HJoinResponse::HJoinResponse(const HJoinResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    sucNode_arraysize = 0;
    this->sucNode_var = 0;
    operator=(other);
}

HJoinResponse::~HJoinResponse()
{
    unsigned int i;
    delete [] sucNode_var;
}

HJoinResponse& HJoinResponse::operator=(const HJoinResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->sucNum_var = other.sucNum_var;
    delete [] this->sucNode_var;
    this->sucNode_var = (other.sucNode_arraysize==0) ? NULL : new NodeHandle[other.sucNode_arraysize];
    sucNode_arraysize = other.sucNode_arraysize;
    for (i=0; i<sucNode_arraysize; i++)
        this->sucNode_var[i] = other.sucNode_var[i];
    this->preNode_var = other.preNode_var;
    this->superPeerNode_var = other.superPeerNode_var;
    this->superPeerPre_var = other.superPeerPre_var;
    return *this;
}

void HJoinResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->sucNum_var);
    b->pack(sucNode_arraysize);
    doPacking(b,this->sucNode_var,sucNode_arraysize);
    doPacking(b,this->preNode_var);
    doPacking(b,this->superPeerNode_var);
    doPacking(b,this->superPeerPre_var);
}

void HJoinResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->sucNum_var);
    delete [] this->sucNode_var;
    b->unpack(sucNode_arraysize);
    if (sucNode_arraysize==0) {
        this->sucNode_var = 0;
    } else {
        this->sucNode_var = new NodeHandle[sucNode_arraysize];
        doUnpacking(b,this->sucNode_var,sucNode_arraysize);
    }
    doUnpacking(b,this->preNode_var);
    doUnpacking(b,this->superPeerNode_var);
    doUnpacking(b,this->superPeerPre_var);
}

int HJoinResponse::getSucNum() const
{
    return sucNum_var;
}

void HJoinResponse::setSucNum(int sucNum_var)
{
    this->sucNum_var = sucNum_var;
}

void HJoinResponse::setSucNodeArraySize(unsigned int size)
{
    NodeHandle *sucNode_var2 = (size==0) ? NULL : new NodeHandle[size];
    unsigned int sz = sucNode_arraysize < size ? sucNode_arraysize : size;
    unsigned int i;
    for (i=0; i<sz; i++)
        sucNode_var2[i] = this->sucNode_var[i];
    sucNode_arraysize = size;
    delete [] this->sucNode_var;
    this->sucNode_var = sucNode_var2;
}

unsigned int HJoinResponse::getSucNodeArraySize() const
{
    return sucNode_arraysize;
}

NodeHandle& HJoinResponse::getSucNode(unsigned int k)
{
    if (k>=sucNode_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", sucNode_arraysize, k);
    return sucNode_var[k];
}

void HJoinResponse::setSucNode(unsigned int k, const NodeHandle& sucNode_var)
{
    if (k>=sucNode_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", sucNode_arraysize, k);
    this->sucNode_var[k]=sucNode_var;
}

NodeHandle& HJoinResponse::getPreNode()
{
    return preNode_var;
}

void HJoinResponse::setPreNode(const NodeHandle& preNode_var)
{
    this->preNode_var = preNode_var;
}

NodeHandle& HJoinResponse::getSuperPeerNode()
{
    return superPeerNode_var;
}

void HJoinResponse::setSuperPeerNode(const NodeHandle& superPeerNode_var)
{
    this->superPeerNode_var = superPeerNode_var;
}

NodeHandle& HJoinResponse::getSuperPeerPre()
{
    return superPeerPre_var;
}

void HJoinResponse::setSuperPeerPre(const NodeHandle& superPeerPre_var)
{
    this->superPeerPre_var = superPeerPre_var;
}

class HJoinResponseDescriptor : public cClassDescriptor
{
  public:
    HJoinResponseDescriptor();
    virtual ~HJoinResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HJoinResponseDescriptor);

HJoinResponseDescriptor::HJoinResponseDescriptor() : cClassDescriptor("HJoinResponse", "HChordMessage")
{
}

HJoinResponseDescriptor::~HJoinResponseDescriptor()
{
}

bool HJoinResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HJoinResponse *>(obj)!=NULL;
}

const char *HJoinResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HJoinResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int HJoinResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        case 1: return FD_ISARRAY | FD_ISCOMPOUND;
        case 2: return FD_ISCOMPOUND;
        case 3: return FD_ISCOMPOUND;
        case 4: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HJoinResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "sucNum";
        case 1: return "sucNode";
        case 2: return "preNode";
        case 3: return "superPeerNode";
        case 4: return "superPeerPre";
        default: return NULL;
    }
}

const char *HJoinResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "int";
        case 1: return "NodeHandle";
        case 2: return "NodeHandle";
        case 3: return "NodeHandle";
        case 4: return "NodeHandle";
        default: return NULL;
    }
}

const char *HJoinResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HJoinResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HJoinResponse *pp _MAYBEUNUSED = (HJoinResponse *)object;
    switch (field) {
        case 1: return pp->getSucNodeArraySize();
        default: return 0;
    }
}

bool HJoinResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HJoinResponse *pp _MAYBEUNUSED = (HJoinResponse *)object;
    switch (field) {
        case 0: long2string(pp->getSucNum(),resultbuf,bufsize); return true;
        case 1: {std::stringstream out; out << pp->getSucNode(i); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 2: {std::stringstream out; out << pp->getPreNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 3: {std::stringstream out; out << pp->getSuperPeerNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 4: {std::stringstream out; out << pp->getSuperPeerPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HJoinResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HJoinResponse *pp _MAYBEUNUSED = (HJoinResponse *)object;
    switch (field) {
        case 0: pp->setSucNum(string2long(value)); return true;
        default: return false;
    }
}

const char *HJoinResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return "NodeHandle"; break;
        case 2: return "NodeHandle"; break;
        case 3: return "NodeHandle"; break;
        case 4: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HJoinResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HJoinResponse *pp _MAYBEUNUSED = (HJoinResponse *)object;
    switch (field) {
        case 1: return (void *)(&pp->getSucNode(i)); break;
        case 2: return (void *)(&pp->getPreNode()); break;
        case 3: return (void *)(&pp->getSuperPeerNode()); break;
        case 4: return (void *)(&pp->getSuperPeerPre()); break;
        default: return NULL;
    }
}

Register_Class(HNotifyCall);

HNotifyCall::HNotifyCall(const char *name, int kind) : HChordMessage(name,kind)
{
}

HNotifyCall::HNotifyCall(const HNotifyCall& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HNotifyCall::~HNotifyCall()
{
    unsigned int i;
}

HNotifyCall& HNotifyCall::operator=(const HNotifyCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HNotifyCall::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HNotifyCall::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HNotifyCallDescriptor : public cClassDescriptor
{
  public:
    HNotifyCallDescriptor();
    virtual ~HNotifyCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HNotifyCallDescriptor);

HNotifyCallDescriptor::HNotifyCallDescriptor() : cClassDescriptor("HNotifyCall", "HChordMessage")
{
}

HNotifyCallDescriptor::~HNotifyCallDescriptor()
{
}

bool HNotifyCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HNotifyCall *>(obj)!=NULL;
}

const char *HNotifyCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HNotifyCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HNotifyCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HNotifyCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HNotifyCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HNotifyCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HNotifyCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyCall *pp _MAYBEUNUSED = (HNotifyCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool HNotifyCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyCall *pp _MAYBEUNUSED = (HNotifyCall *)object;
    switch (field) {
        default: return false;
    }
}

bool HNotifyCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyCall *pp _MAYBEUNUSED = (HNotifyCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *HNotifyCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HNotifyCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyCall *pp _MAYBEUNUSED = (HNotifyCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HNotifyResponse);

HNotifyResponse::HNotifyResponse(const char *name, int kind) : HChordMessage(name,kind)
{
    unsigned int i;
    sucNode_arraysize = 0;
    this->sucNode_var = 0;
    this->sucNum_var = 0;
}

HNotifyResponse::HNotifyResponse(const HNotifyResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    sucNode_arraysize = 0;
    this->sucNode_var = 0;
    operator=(other);
}

HNotifyResponse::~HNotifyResponse()
{
    unsigned int i;
    delete [] sucNode_var;
}

HNotifyResponse& HNotifyResponse::operator=(const HNotifyResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->srcNode_var = other.srcNode_var;
    delete [] this->sucNode_var;
    this->sucNode_var = (other.sucNode_arraysize==0) ? NULL : new NodeHandle[other.sucNode_arraysize];
    sucNode_arraysize = other.sucNode_arraysize;
    for (i=0; i<sucNode_arraysize; i++)
        this->sucNode_var[i] = other.sucNode_var[i];
    this->sucNum_var = other.sucNum_var;
    return *this;
}

void HNotifyResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->srcNode_var);
    b->pack(sucNode_arraysize);
    doPacking(b,this->sucNode_var,sucNode_arraysize);
    doPacking(b,this->sucNum_var);
}

void HNotifyResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->srcNode_var);
    delete [] this->sucNode_var;
    b->unpack(sucNode_arraysize);
    if (sucNode_arraysize==0) {
        this->sucNode_var = 0;
    } else {
        this->sucNode_var = new NodeHandle[sucNode_arraysize];
        doUnpacking(b,this->sucNode_var,sucNode_arraysize);
    }
    doUnpacking(b,this->sucNum_var);
}

NodeHandle& HNotifyResponse::getSrcNode()
{
    return srcNode_var;
}

void HNotifyResponse::setSrcNode(const NodeHandle& srcNode_var)
{
    this->srcNode_var = srcNode_var;
}

void HNotifyResponse::setSucNodeArraySize(unsigned int size)
{
    NodeHandle *sucNode_var2 = (size==0) ? NULL : new NodeHandle[size];
    unsigned int sz = sucNode_arraysize < size ? sucNode_arraysize : size;
    unsigned int i;
    for (i=0; i<sz; i++)
        sucNode_var2[i] = this->sucNode_var[i];
    sucNode_arraysize = size;
    delete [] this->sucNode_var;
    this->sucNode_var = sucNode_var2;
}

unsigned int HNotifyResponse::getSucNodeArraySize() const
{
    return sucNode_arraysize;
}

NodeHandle& HNotifyResponse::getSucNode(unsigned int k)
{
    if (k>=sucNode_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", sucNode_arraysize, k);
    return sucNode_var[k];
}

void HNotifyResponse::setSucNode(unsigned int k, const NodeHandle& sucNode_var)
{
    if (k>=sucNode_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", sucNode_arraysize, k);
    this->sucNode_var[k]=sucNode_var;
}

int HNotifyResponse::getSucNum() const
{
    return sucNum_var;
}

void HNotifyResponse::setSucNum(int sucNum_var)
{
    this->sucNum_var = sucNum_var;
}

class HNotifyResponseDescriptor : public cClassDescriptor
{
  public:
    HNotifyResponseDescriptor();
    virtual ~HNotifyResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HNotifyResponseDescriptor);

HNotifyResponseDescriptor::HNotifyResponseDescriptor() : cClassDescriptor("HNotifyResponse", "HChordMessage")
{
}

HNotifyResponseDescriptor::~HNotifyResponseDescriptor()
{
}

bool HNotifyResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HNotifyResponse *>(obj)!=NULL;
}

const char *HNotifyResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HNotifyResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int HNotifyResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        case 1: return FD_ISARRAY | FD_ISCOMPOUND;
        case 2: return FD_ISEDITABLE;
        default: return 0;
    }
}

const char *HNotifyResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "srcNode";
        case 1: return "sucNode";
        case 2: return "sucNum";
        default: return NULL;
    }
}

const char *HNotifyResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        case 2: return "int";
        default: return NULL;
    }
}

const char *HNotifyResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HNotifyResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyResponse *pp _MAYBEUNUSED = (HNotifyResponse *)object;
    switch (field) {
        case 1: return pp->getSucNodeArraySize();
        default: return 0;
    }
}

bool HNotifyResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyResponse *pp _MAYBEUNUSED = (HNotifyResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getSucNode(i); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 2: long2string(pp->getSucNum(),resultbuf,bufsize); return true;
        default: return false;
    }
}

bool HNotifyResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyResponse *pp _MAYBEUNUSED = (HNotifyResponse *)object;
    switch (field) {
        case 2: pp->setSucNum(string2long(value)); return true;
        default: return false;
    }
}

const char *HNotifyResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HNotifyResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HNotifyResponse *pp _MAYBEUNUSED = (HNotifyResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getSrcNode()); break;
        case 1: return (void *)(&pp->getSucNode(i)); break;
        default: return NULL;
    }
}

Register_Class(HNewSuccessorHintMsg);

HNewSuccessorHintMsg::HNewSuccessorHintMsg(const char *name, int kind) : HChordMessage(name,kind)
{
}

HNewSuccessorHintMsg::HNewSuccessorHintMsg(const HNewSuccessorHintMsg& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HNewSuccessorHintMsg::~HNewSuccessorHintMsg()
{
    unsigned int i;
}

HNewSuccessorHintMsg& HNewSuccessorHintMsg::operator=(const HNewSuccessorHintMsg& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->pre_var = other.pre_var;
    return *this;
}

void HNewSuccessorHintMsg::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->pre_var);
}

void HNewSuccessorHintMsg::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->pre_var);
}

NodeHandle& HNewSuccessorHintMsg::getPre()
{
    return pre_var;
}

void HNewSuccessorHintMsg::setPre(const NodeHandle& pre_var)
{
    this->pre_var = pre_var;
}

class HNewSuccessorHintMsgDescriptor : public cClassDescriptor
{
  public:
    HNewSuccessorHintMsgDescriptor();
    virtual ~HNewSuccessorHintMsgDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HNewSuccessorHintMsgDescriptor);

HNewSuccessorHintMsgDescriptor::HNewSuccessorHintMsgDescriptor() : cClassDescriptor("HNewSuccessorHintMsg", "HChordMessage")
{
}

HNewSuccessorHintMsgDescriptor::~HNewSuccessorHintMsgDescriptor()
{
}

bool HNewSuccessorHintMsgDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HNewSuccessorHintMsg *>(obj)!=NULL;
}

const char *HNewSuccessorHintMsgDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HNewSuccessorHintMsgDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int HNewSuccessorHintMsgDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HNewSuccessorHintMsgDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "pre";
        default: return NULL;
    }
}

const char *HNewSuccessorHintMsgDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        default: return NULL;
    }
}

const char *HNewSuccessorHintMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HNewSuccessorHintMsgDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HNewSuccessorHintMsg *pp _MAYBEUNUSED = (HNewSuccessorHintMsg *)object;
    switch (field) {
        default: return 0;
    }
}

bool HNewSuccessorHintMsgDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HNewSuccessorHintMsg *pp _MAYBEUNUSED = (HNewSuccessorHintMsg *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HNewSuccessorHintMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HNewSuccessorHintMsg *pp _MAYBEUNUSED = (HNewSuccessorHintMsg *)object;
    switch (field) {
        default: return false;
    }
}

const char *HNewSuccessorHintMsgDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HNewSuccessorHintMsgDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HNewSuccessorHintMsg *pp _MAYBEUNUSED = (HNewSuccessorHintMsg *)object;
    switch (field) {
        case 0: return (void *)(&pp->getPre()); break;
        default: return NULL;
    }
}

Register_Class(HStabilizeCall);

HStabilizeCall::HStabilizeCall(const char *name, int kind) : HChordMessage(name,kind)
{
}

HStabilizeCall::HStabilizeCall(const HStabilizeCall& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HStabilizeCall::~HStabilizeCall()
{
    unsigned int i;
}

HStabilizeCall& HStabilizeCall::operator=(const HStabilizeCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HStabilizeCall::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HStabilizeCall::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HStabilizeCallDescriptor : public cClassDescriptor
{
  public:
    HStabilizeCallDescriptor();
    virtual ~HStabilizeCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HStabilizeCallDescriptor);

HStabilizeCallDescriptor::HStabilizeCallDescriptor() : cClassDescriptor("HStabilizeCall", "HChordMessage")
{
}

HStabilizeCallDescriptor::~HStabilizeCallDescriptor()
{
}

bool HStabilizeCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HStabilizeCall *>(obj)!=NULL;
}

const char *HStabilizeCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HStabilizeCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HStabilizeCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HStabilizeCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HStabilizeCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HStabilizeCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HStabilizeCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeCall *pp _MAYBEUNUSED = (HStabilizeCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool HStabilizeCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeCall *pp _MAYBEUNUSED = (HStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

bool HStabilizeCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeCall *pp _MAYBEUNUSED = (HStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *HStabilizeCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HStabilizeCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeCall *pp _MAYBEUNUSED = (HStabilizeCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HStabilizeResponse);

HStabilizeResponse::HStabilizeResponse(const char *name, int kind) : HChordMessage(name,kind)
{
}

HStabilizeResponse::HStabilizeResponse(const HStabilizeResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HStabilizeResponse::~HStabilizeResponse()
{
    unsigned int i;
}

HStabilizeResponse& HStabilizeResponse::operator=(const HStabilizeResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->pre_var = other.pre_var;
    return *this;
}

void HStabilizeResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->pre_var);
}

void HStabilizeResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->pre_var);
}

NodeHandle& HStabilizeResponse::getPre()
{
    return pre_var;
}

void HStabilizeResponse::setPre(const NodeHandle& pre_var)
{
    this->pre_var = pre_var;
}

class HStabilizeResponseDescriptor : public cClassDescriptor
{
  public:
    HStabilizeResponseDescriptor();
    virtual ~HStabilizeResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HStabilizeResponseDescriptor);

HStabilizeResponseDescriptor::HStabilizeResponseDescriptor() : cClassDescriptor("HStabilizeResponse", "HChordMessage")
{
}

HStabilizeResponseDescriptor::~HStabilizeResponseDescriptor()
{
}

bool HStabilizeResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HStabilizeResponse *>(obj)!=NULL;
}

const char *HStabilizeResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HStabilizeResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int HStabilizeResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HStabilizeResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "pre";
        default: return NULL;
    }
}

const char *HStabilizeResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        default: return NULL;
    }
}

const char *HStabilizeResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HStabilizeResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeResponse *pp _MAYBEUNUSED = (HStabilizeResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool HStabilizeResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeResponse *pp _MAYBEUNUSED = (HStabilizeResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HStabilizeResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeResponse *pp _MAYBEUNUSED = (HStabilizeResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *HStabilizeResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HStabilizeResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeResponse *pp _MAYBEUNUSED = (HStabilizeResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getPre()); break;
        default: return NULL;
    }
}

Register_Class(HFixfingersCall);

HFixfingersCall::HFixfingersCall(const char *name, int kind) : HChordMessage(name,kind)
{
    this->finger_var = 0;
}

HFixfingersCall::HFixfingersCall(const HFixfingersCall& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HFixfingersCall::~HFixfingersCall()
{
    unsigned int i;
}

HFixfingersCall& HFixfingersCall::operator=(const HFixfingersCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->finger_var = other.finger_var;
    this->lookupKey_var = other.lookupKey_var;
    return *this;
}

void HFixfingersCall::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->finger_var);
    doPacking(b,this->lookupKey_var);
}

void HFixfingersCall::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->finger_var);
    doUnpacking(b,this->lookupKey_var);
}

int HFixfingersCall::getFinger() const
{
    return finger_var;
}

void HFixfingersCall::setFinger(int finger_var)
{
    this->finger_var = finger_var;
}

OverlayKey& HFixfingersCall::getLookupKey()
{
    return lookupKey_var;
}

void HFixfingersCall::setLookupKey(const OverlayKey& lookupKey_var)
{
    this->lookupKey_var = lookupKey_var;
}

class HFixfingersCallDescriptor : public cClassDescriptor
{
  public:
    HFixfingersCallDescriptor();
    virtual ~HFixfingersCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HFixfingersCallDescriptor);

HFixfingersCallDescriptor::HFixfingersCallDescriptor() : cClassDescriptor("HFixfingersCall", "HChordMessage")
{
}

HFixfingersCallDescriptor::~HFixfingersCallDescriptor()
{
}

bool HFixfingersCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HFixfingersCall *>(obj)!=NULL;
}

const char *HFixfingersCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HFixfingersCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HFixfingersCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HFixfingersCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "finger";
        case 1: return "lookupKey";
        default: return NULL;
    }
}

const char *HFixfingersCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "int";
        case 1: return "OverlayKey";
        default: return NULL;
    }
}

const char *HFixfingersCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HFixfingersCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersCall *pp _MAYBEUNUSED = (HFixfingersCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool HFixfingersCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersCall *pp _MAYBEUNUSED = (HFixfingersCall *)object;
    switch (field) {
        case 0: long2string(pp->getFinger(),resultbuf,bufsize); return true;
        case 1: {std::stringstream out; out << pp->getLookupKey(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HFixfingersCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersCall *pp _MAYBEUNUSED = (HFixfingersCall *)object;
    switch (field) {
        case 0: pp->setFinger(string2long(value)); return true;
        default: return false;
    }
}

const char *HFixfingersCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return "OverlayKey"; break;
        default: return NULL;
    }
}

void *HFixfingersCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersCall *pp _MAYBEUNUSED = (HFixfingersCall *)object;
    switch (field) {
        case 1: return (void *)(&pp->getLookupKey()); break;
        default: return NULL;
    }
}

Register_Class(HFixfingersResponse);

HFixfingersResponse::HFixfingersResponse(const char *name, int kind) : HChordMessage(name,kind)
{
    this->finger_var = 0;
}

HFixfingersResponse::HFixfingersResponse(const HFixfingersResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HFixfingersResponse::~HFixfingersResponse()
{
    unsigned int i;
}

HFixfingersResponse& HFixfingersResponse::operator=(const HFixfingersResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->finger_var = other.finger_var;
    this->sucNode_var = other.sucNode_var;
    return *this;
}

void HFixfingersResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->finger_var);
    doPacking(b,this->sucNode_var);
}

void HFixfingersResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->finger_var);
    doUnpacking(b,this->sucNode_var);
}

int HFixfingersResponse::getFinger() const
{
    return finger_var;
}

void HFixfingersResponse::setFinger(int finger_var)
{
    this->finger_var = finger_var;
}

NodeHandle& HFixfingersResponse::getSucNode()
{
    return sucNode_var;
}

void HFixfingersResponse::setSucNode(const NodeHandle& sucNode_var)
{
    this->sucNode_var = sucNode_var;
}

class HFixfingersResponseDescriptor : public cClassDescriptor
{
  public:
    HFixfingersResponseDescriptor();
    virtual ~HFixfingersResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HFixfingersResponseDescriptor);

HFixfingersResponseDescriptor::HFixfingersResponseDescriptor() : cClassDescriptor("HFixfingersResponse", "HChordMessage")
{
}

HFixfingersResponseDescriptor::~HFixfingersResponseDescriptor()
{
}

bool HFixfingersResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HFixfingersResponse *>(obj)!=NULL;
}

const char *HFixfingersResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HFixfingersResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HFixfingersResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HFixfingersResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "finger";
        case 1: return "sucNode";
        default: return NULL;
    }
}

const char *HFixfingersResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "int";
        case 1: return "NodeHandle";
        default: return NULL;
    }
}

const char *HFixfingersResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HFixfingersResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersResponse *pp _MAYBEUNUSED = (HFixfingersResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool HFixfingersResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersResponse *pp _MAYBEUNUSED = (HFixfingersResponse *)object;
    switch (field) {
        case 0: long2string(pp->getFinger(),resultbuf,bufsize); return true;
        case 1: {std::stringstream out; out << pp->getSucNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HFixfingersResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersResponse *pp _MAYBEUNUSED = (HFixfingersResponse *)object;
    switch (field) {
        case 0: pp->setFinger(string2long(value)); return true;
        default: return false;
    }
}

const char *HFixfingersResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HFixfingersResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HFixfingersResponse *pp _MAYBEUNUSED = (HFixfingersResponse *)object;
    switch (field) {
        case 1: return (void *)(&pp->getSucNode()); break;
        default: return NULL;
    }
}

Register_Class(HMigrateRequest);

HMigrateRequest::HMigrateRequest(const char *name, int kind) : HChordMessage(name,kind)
{
}

HMigrateRequest::HMigrateRequest(const HMigrateRequest& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HMigrateRequest::~HMigrateRequest()
{
    unsigned int i;
}

HMigrateRequest& HMigrateRequest::operator=(const HMigrateRequest& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HMigrateRequest::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HMigrateRequest::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HMigrateRequestDescriptor : public cClassDescriptor
{
  public:
    HMigrateRequestDescriptor();
    virtual ~HMigrateRequestDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HMigrateRequestDescriptor);

HMigrateRequestDescriptor::HMigrateRequestDescriptor() : cClassDescriptor("HMigrateRequest", "HChordMessage")
{
}

HMigrateRequestDescriptor::~HMigrateRequestDescriptor()
{
}

bool HMigrateRequestDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HMigrateRequest *>(obj)!=NULL;
}

const char *HMigrateRequestDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HMigrateRequestDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HMigrateRequestDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HMigrateRequestDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HMigrateRequestDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HMigrateRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HMigrateRequestDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateRequest *pp _MAYBEUNUSED = (HMigrateRequest *)object;
    switch (field) {
        default: return 0;
    }
}

bool HMigrateRequestDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateRequest *pp _MAYBEUNUSED = (HMigrateRequest *)object;
    switch (field) {
        default: return false;
    }
}

bool HMigrateRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateRequest *pp _MAYBEUNUSED = (HMigrateRequest *)object;
    switch (field) {
        default: return false;
    }
}

const char *HMigrateRequestDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HMigrateRequestDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateRequest *pp _MAYBEUNUSED = (HMigrateRequest *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HMigrateResponse);

HMigrateResponse::HMigrateResponse(const char *name, int kind) : HChordMessage(name,kind)
{
}

HMigrateResponse::HMigrateResponse(const HMigrateResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HMigrateResponse::~HMigrateResponse()
{
    unsigned int i;
}

HMigrateResponse& HMigrateResponse::operator=(const HMigrateResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HMigrateResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HMigrateResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HMigrateResponseDescriptor : public cClassDescriptor
{
  public:
    HMigrateResponseDescriptor();
    virtual ~HMigrateResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HMigrateResponseDescriptor);

HMigrateResponseDescriptor::HMigrateResponseDescriptor() : cClassDescriptor("HMigrateResponse", "HChordMessage")
{
}

HMigrateResponseDescriptor::~HMigrateResponseDescriptor()
{
}

bool HMigrateResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HMigrateResponse *>(obj)!=NULL;
}

const char *HMigrateResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HMigrateResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HMigrateResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HMigrateResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HMigrateResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HMigrateResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HMigrateResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateResponse *pp _MAYBEUNUSED = (HMigrateResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool HMigrateResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateResponse *pp _MAYBEUNUSED = (HMigrateResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool HMigrateResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateResponse *pp _MAYBEUNUSED = (HMigrateResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *HMigrateResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HMigrateResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HMigrateResponse *pp _MAYBEUNUSED = (HMigrateResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HStabilizeSuperPeerCall);

HStabilizeSuperPeerCall::HStabilizeSuperPeerCall(const char *name, int kind) : HChordMessage(name,kind)
{
    this->largest_var = false;
}

HStabilizeSuperPeerCall::HStabilizeSuperPeerCall(const HStabilizeSuperPeerCall& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HStabilizeSuperPeerCall::~HStabilizeSuperPeerCall()
{
    unsigned int i;
}

HStabilizeSuperPeerCall& HStabilizeSuperPeerCall::operator=(const HStabilizeSuperPeerCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->largest_var = other.largest_var;
    this->Suc_var = other.Suc_var;
    return *this;
}

void HStabilizeSuperPeerCall::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->largest_var);
    doPacking(b,this->Suc_var);
}

void HStabilizeSuperPeerCall::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->largest_var);
    doUnpacking(b,this->Suc_var);
}

bool HStabilizeSuperPeerCall::getLargest() const
{
    return largest_var;
}

void HStabilizeSuperPeerCall::setLargest(bool largest_var)
{
    this->largest_var = largest_var;
}

NodeHandle& HStabilizeSuperPeerCall::getSuc()
{
    return Suc_var;
}

void HStabilizeSuperPeerCall::setSuc(const NodeHandle& Suc_var)
{
    this->Suc_var = Suc_var;
}

class HStabilizeSuperPeerCallDescriptor : public cClassDescriptor
{
  public:
    HStabilizeSuperPeerCallDescriptor();
    virtual ~HStabilizeSuperPeerCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HStabilizeSuperPeerCallDescriptor);

HStabilizeSuperPeerCallDescriptor::HStabilizeSuperPeerCallDescriptor() : cClassDescriptor("HStabilizeSuperPeerCall", "HChordMessage")
{
}

HStabilizeSuperPeerCallDescriptor::~HStabilizeSuperPeerCallDescriptor()
{
}

bool HStabilizeSuperPeerCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HStabilizeSuperPeerCall *>(obj)!=NULL;
}

const char *HStabilizeSuperPeerCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HStabilizeSuperPeerCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HStabilizeSuperPeerCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISEDITABLE;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HStabilizeSuperPeerCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "largest";
        case 1: return "Suc";
        default: return NULL;
    }
}

const char *HStabilizeSuperPeerCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "bool";
        case 1: return "NodeHandle";
        default: return NULL;
    }
}

const char *HStabilizeSuperPeerCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HStabilizeSuperPeerCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerCall *pp _MAYBEUNUSED = (HStabilizeSuperPeerCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool HStabilizeSuperPeerCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerCall *pp _MAYBEUNUSED = (HStabilizeSuperPeerCall *)object;
    switch (field) {
        case 0: bool2string(pp->getLargest(),resultbuf,bufsize); return true;
        case 1: {std::stringstream out; out << pp->getSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HStabilizeSuperPeerCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerCall *pp _MAYBEUNUSED = (HStabilizeSuperPeerCall *)object;
    switch (field) {
        case 0: pp->setLargest(string2bool(value)); return true;
        default: return false;
    }
}

const char *HStabilizeSuperPeerCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HStabilizeSuperPeerCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerCall *pp _MAYBEUNUSED = (HStabilizeSuperPeerCall *)object;
    switch (field) {
        case 1: return (void *)(&pp->getSuc()); break;
        default: return NULL;
    }
}

Register_Class(HStabilizeSuperPeerResponse);

HStabilizeSuperPeerResponse::HStabilizeSuperPeerResponse(const char *name, int kind) : HChordMessage(name,kind)
{
    unsigned int i;
    strongPeers_arraysize = 0;
    this->strongPeers_var = 0;
    this->num_var = 0;
}

HStabilizeSuperPeerResponse::HStabilizeSuperPeerResponse(const HStabilizeSuperPeerResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    strongPeers_arraysize = 0;
    this->strongPeers_var = 0;
    operator=(other);
}

HStabilizeSuperPeerResponse::~HStabilizeSuperPeerResponse()
{
    unsigned int i;
    delete [] strongPeers_var;
}

HStabilizeSuperPeerResponse& HStabilizeSuperPeerResponse::operator=(const HStabilizeSuperPeerResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    delete [] this->strongPeers_var;
    this->strongPeers_var = (other.strongPeers_arraysize==0) ? NULL : new NodeHandle[other.strongPeers_arraysize];
    strongPeers_arraysize = other.strongPeers_arraysize;
    for (i=0; i<strongPeers_arraysize; i++)
        this->strongPeers_var[i] = other.strongPeers_var[i];
    this->preNode_var = other.preNode_var;
    this->num_var = other.num_var;
    return *this;
}

void HStabilizeSuperPeerResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    b->pack(strongPeers_arraysize);
    doPacking(b,this->strongPeers_var,strongPeers_arraysize);
    doPacking(b,this->preNode_var);
    doPacking(b,this->num_var);
}

void HStabilizeSuperPeerResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    delete [] this->strongPeers_var;
    b->unpack(strongPeers_arraysize);
    if (strongPeers_arraysize==0) {
        this->strongPeers_var = 0;
    } else {
        this->strongPeers_var = new NodeHandle[strongPeers_arraysize];
        doUnpacking(b,this->strongPeers_var,strongPeers_arraysize);
    }
    doUnpacking(b,this->preNode_var);
    doUnpacking(b,this->num_var);
}

void HStabilizeSuperPeerResponse::setStrongPeersArraySize(unsigned int size)
{
    NodeHandle *strongPeers_var2 = (size==0) ? NULL : new NodeHandle[size];
    unsigned int sz = strongPeers_arraysize < size ? strongPeers_arraysize : size;
    unsigned int i;
    for (i=0; i<sz; i++)
        strongPeers_var2[i] = this->strongPeers_var[i];
    strongPeers_arraysize = size;
    delete [] this->strongPeers_var;
    this->strongPeers_var = strongPeers_var2;
}

unsigned int HStabilizeSuperPeerResponse::getStrongPeersArraySize() const
{
    return strongPeers_arraysize;
}

NodeHandle& HStabilizeSuperPeerResponse::getStrongPeers(unsigned int k)
{
    if (k>=strongPeers_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", strongPeers_arraysize, k);
    return strongPeers_var[k];
}

void HStabilizeSuperPeerResponse::setStrongPeers(unsigned int k, const NodeHandle& strongPeers_var)
{
    if (k>=strongPeers_arraysize) throw new cRuntimeError("Array of size %d indexed by %d", strongPeers_arraysize, k);
    this->strongPeers_var[k]=strongPeers_var;
}

NodeHandle& HStabilizeSuperPeerResponse::getPreNode()
{
    return preNode_var;
}

void HStabilizeSuperPeerResponse::setPreNode(const NodeHandle& preNode_var)
{
    this->preNode_var = preNode_var;
}

int HStabilizeSuperPeerResponse::getNum() const
{
    return num_var;
}

void HStabilizeSuperPeerResponse::setNum(int num_var)
{
    this->num_var = num_var;
}

class HStabilizeSuperPeerResponseDescriptor : public cClassDescriptor
{
  public:
    HStabilizeSuperPeerResponseDescriptor();
    virtual ~HStabilizeSuperPeerResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HStabilizeSuperPeerResponseDescriptor);

HStabilizeSuperPeerResponseDescriptor::HStabilizeSuperPeerResponseDescriptor() : cClassDescriptor("HStabilizeSuperPeerResponse", "HChordMessage")
{
}

HStabilizeSuperPeerResponseDescriptor::~HStabilizeSuperPeerResponseDescriptor()
{
}

bool HStabilizeSuperPeerResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HStabilizeSuperPeerResponse *>(obj)!=NULL;
}

const char *HStabilizeSuperPeerResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HStabilizeSuperPeerResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int HStabilizeSuperPeerResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISARRAY | FD_ISCOMPOUND;
        case 1: return FD_ISCOMPOUND;
        case 2: return FD_ISEDITABLE;
        default: return 0;
    }
}

const char *HStabilizeSuperPeerResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "strongPeers";
        case 1: return "preNode";
        case 2: return "num";
        default: return NULL;
    }
}

const char *HStabilizeSuperPeerResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        case 2: return "int";
        default: return NULL;
    }
}

const char *HStabilizeSuperPeerResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HStabilizeSuperPeerResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerResponse *pp _MAYBEUNUSED = (HStabilizeSuperPeerResponse *)object;
    switch (field) {
        case 0: return pp->getStrongPeersArraySize();
        default: return 0;
    }
}

bool HStabilizeSuperPeerResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerResponse *pp _MAYBEUNUSED = (HStabilizeSuperPeerResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getStrongPeers(i); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getPreNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 2: long2string(pp->getNum(),resultbuf,bufsize); return true;
        default: return false;
    }
}

bool HStabilizeSuperPeerResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerResponse *pp _MAYBEUNUSED = (HStabilizeSuperPeerResponse *)object;
    switch (field) {
        case 2: pp->setNum(string2long(value)); return true;
        default: return false;
    }
}

const char *HStabilizeSuperPeerResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HStabilizeSuperPeerResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HStabilizeSuperPeerResponse *pp _MAYBEUNUSED = (HStabilizeSuperPeerResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getStrongPeers(i)); break;
        case 1: return (void *)(&pp->getPreNode()); break;
        default: return NULL;
    }
}

Register_Class(HLargestNodeRequest);

HLargestNodeRequest::HLargestNodeRequest(const char *name, int kind) : HChordMessage(name,kind)
{
}

HLargestNodeRequest::HLargestNodeRequest(const HLargestNodeRequest& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HLargestNodeRequest::~HLargestNodeRequest()
{
    unsigned int i;
}

HLargestNodeRequest& HLargestNodeRequest::operator=(const HLargestNodeRequest& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    return *this;
}

void HLargestNodeRequest::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
}

void HLargestNodeRequest::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
}

class HLargestNodeRequestDescriptor : public cClassDescriptor
{
  public:
    HLargestNodeRequestDescriptor();
    virtual ~HLargestNodeRequestDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HLargestNodeRequestDescriptor);

HLargestNodeRequestDescriptor::HLargestNodeRequestDescriptor() : cClassDescriptor("HLargestNodeRequest", "HChordMessage")
{
}

HLargestNodeRequestDescriptor::~HLargestNodeRequestDescriptor()
{
}

bool HLargestNodeRequestDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HLargestNodeRequest *>(obj)!=NULL;
}

const char *HLargestNodeRequestDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HLargestNodeRequestDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int HLargestNodeRequestDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *HLargestNodeRequestDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HLargestNodeRequestDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *HLargestNodeRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HLargestNodeRequestDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeRequest *pp _MAYBEUNUSED = (HLargestNodeRequest *)object;
    switch (field) {
        default: return 0;
    }
}

bool HLargestNodeRequestDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeRequest *pp _MAYBEUNUSED = (HLargestNodeRequest *)object;
    switch (field) {
        default: return false;
    }
}

bool HLargestNodeRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeRequest *pp _MAYBEUNUSED = (HLargestNodeRequest *)object;
    switch (field) {
        default: return false;
    }
}

const char *HLargestNodeRequestDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *HLargestNodeRequestDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeRequest *pp _MAYBEUNUSED = (HLargestNodeRequest *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(HLargestNodeResponse);

HLargestNodeResponse::HLargestNodeResponse(const char *name, int kind) : HChordMessage(name,kind)
{
}

HLargestNodeResponse::HLargestNodeResponse(const HLargestNodeResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HLargestNodeResponse::~HLargestNodeResponse()
{
    unsigned int i;
}

HLargestNodeResponse& HLargestNodeResponse::operator=(const HLargestNodeResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->node_var = other.node_var;
    this->suc_var = other.suc_var;
    return *this;
}

void HLargestNodeResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->node_var);
    doPacking(b,this->suc_var);
}

void HLargestNodeResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->node_var);
    doUnpacking(b,this->suc_var);
}

NodeHandle& HLargestNodeResponse::getNode()
{
    return node_var;
}

void HLargestNodeResponse::setNode(const NodeHandle& node_var)
{
    this->node_var = node_var;
}

NodeHandle& HLargestNodeResponse::getSuc()
{
    return suc_var;
}

void HLargestNodeResponse::setSuc(const NodeHandle& suc_var)
{
    this->suc_var = suc_var;
}

class HLargestNodeResponseDescriptor : public cClassDescriptor
{
  public:
    HLargestNodeResponseDescriptor();
    virtual ~HLargestNodeResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HLargestNodeResponseDescriptor);

HLargestNodeResponseDescriptor::HLargestNodeResponseDescriptor() : cClassDescriptor("HLargestNodeResponse", "HChordMessage")
{
}

HLargestNodeResponseDescriptor::~HLargestNodeResponseDescriptor()
{
}

bool HLargestNodeResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HLargestNodeResponse *>(obj)!=NULL;
}

const char *HLargestNodeResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HLargestNodeResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HLargestNodeResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HLargestNodeResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "node";
        case 1: return "suc";
        default: return NULL;
    }
}

const char *HLargestNodeResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        default: return NULL;
    }
}

const char *HLargestNodeResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HLargestNodeResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeResponse *pp _MAYBEUNUSED = (HLargestNodeResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool HLargestNodeResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeResponse *pp _MAYBEUNUSED = (HLargestNodeResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getNode(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HLargestNodeResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeResponse *pp _MAYBEUNUSED = (HLargestNodeResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *HLargestNodeResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HLargestNodeResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HLargestNodeResponse *pp _MAYBEUNUSED = (HLargestNodeResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getNode()); break;
        case 1: return (void *)(&pp->getSuc()); break;
        default: return NULL;
    }
}

Register_Class(HChangePredecessor);

HChangePredecessor::HChangePredecessor(const char *name, int kind) : HChordMessage(name,kind)
{
}

HChangePredecessor::HChangePredecessor(const HChangePredecessor& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HChangePredecessor::~HChangePredecessor()
{
    unsigned int i;
}

HChangePredecessor& HChangePredecessor::operator=(const HChangePredecessor& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->newPre_var = other.newPre_var;
    return *this;
}

void HChangePredecessor::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->newPre_var);
}

void HChangePredecessor::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->newPre_var);
}

NodeHandle& HChangePredecessor::getNewPre()
{
    return newPre_var;
}

void HChangePredecessor::setNewPre(const NodeHandle& newPre_var)
{
    this->newPre_var = newPre_var;
}

class HChangePredecessorDescriptor : public cClassDescriptor
{
  public:
    HChangePredecessorDescriptor();
    virtual ~HChangePredecessorDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HChangePredecessorDescriptor);

HChangePredecessorDescriptor::HChangePredecessorDescriptor() : cClassDescriptor("HChangePredecessor", "HChordMessage")
{
}

HChangePredecessorDescriptor::~HChangePredecessorDescriptor()
{
}

bool HChangePredecessorDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HChangePredecessor *>(obj)!=NULL;
}

const char *HChangePredecessorDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HChangePredecessorDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int HChangePredecessorDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HChangePredecessorDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "newPre";
        default: return NULL;
    }
}

const char *HChangePredecessorDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        default: return NULL;
    }
}

const char *HChangePredecessorDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HChangePredecessorDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HChangePredecessor *pp _MAYBEUNUSED = (HChangePredecessor *)object;
    switch (field) {
        default: return 0;
    }
}

bool HChangePredecessorDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HChangePredecessor *pp _MAYBEUNUSED = (HChangePredecessor *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getNewPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HChangePredecessorDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HChangePredecessor *pp _MAYBEUNUSED = (HChangePredecessor *)object;
    switch (field) {
        default: return false;
    }
}

const char *HChangePredecessorDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HChangePredecessorDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HChangePredecessor *pp _MAYBEUNUSED = (HChangePredecessor *)object;
    switch (field) {
        case 0: return (void *)(&pp->getNewPre()); break;
        default: return NULL;
    }
}

Register_Class(HChangeSuccessorRequest);

HChangeSuccessorRequest::HChangeSuccessorRequest(const char *name, int kind) : HChordMessage(name,kind)
{
}

HChangeSuccessorRequest::HChangeSuccessorRequest(const HChangeSuccessorRequest& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HChangeSuccessorRequest::~HChangeSuccessorRequest()
{
    unsigned int i;
}

HChangeSuccessorRequest& HChangeSuccessorRequest::operator=(const HChangeSuccessorRequest& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->newSuc_var = other.newSuc_var;
    this->newPre_var = other.newPre_var;
    return *this;
}

void HChangeSuccessorRequest::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->newSuc_var);
    doPacking(b,this->newPre_var);
}

void HChangeSuccessorRequest::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->newSuc_var);
    doUnpacking(b,this->newPre_var);
}

NodeHandle& HChangeSuccessorRequest::getNewSuc()
{
    return newSuc_var;
}

void HChangeSuccessorRequest::setNewSuc(const NodeHandle& newSuc_var)
{
    this->newSuc_var = newSuc_var;
}

NodeHandle& HChangeSuccessorRequest::getNewPre()
{
    return newPre_var;
}

void HChangeSuccessorRequest::setNewPre(const NodeHandle& newPre_var)
{
    this->newPre_var = newPre_var;
}

class HChangeSuccessorRequestDescriptor : public cClassDescriptor
{
  public:
    HChangeSuccessorRequestDescriptor();
    virtual ~HChangeSuccessorRequestDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HChangeSuccessorRequestDescriptor);

HChangeSuccessorRequestDescriptor::HChangeSuccessorRequestDescriptor() : cClassDescriptor("HChangeSuccessorRequest", "HChordMessage")
{
}

HChangeSuccessorRequestDescriptor::~HChangeSuccessorRequestDescriptor()
{
}

bool HChangeSuccessorRequestDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HChangeSuccessorRequest *>(obj)!=NULL;
}

const char *HChangeSuccessorRequestDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HChangeSuccessorRequestDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HChangeSuccessorRequestDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HChangeSuccessorRequestDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "newSuc";
        case 1: return "newPre";
        default: return NULL;
    }
}

const char *HChangeSuccessorRequestDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        default: return NULL;
    }
}

const char *HChangeSuccessorRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HChangeSuccessorRequestDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorRequest *pp _MAYBEUNUSED = (HChangeSuccessorRequest *)object;
    switch (field) {
        default: return 0;
    }
}

bool HChangeSuccessorRequestDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorRequest *pp _MAYBEUNUSED = (HChangeSuccessorRequest *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getNewSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getNewPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HChangeSuccessorRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorRequest *pp _MAYBEUNUSED = (HChangeSuccessorRequest *)object;
    switch (field) {
        default: return false;
    }
}

const char *HChangeSuccessorRequestDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HChangeSuccessorRequestDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorRequest *pp _MAYBEUNUSED = (HChangeSuccessorRequest *)object;
    switch (field) {
        case 0: return (void *)(&pp->getNewSuc()); break;
        case 1: return (void *)(&pp->getNewPre()); break;
        default: return NULL;
    }
}

Register_Class(HChangeSuccessorResponse);

HChangeSuccessorResponse::HChangeSuccessorResponse(const char *name, int kind) : HChordMessage(name,kind)
{
}

HChangeSuccessorResponse::HChangeSuccessorResponse(const HChangeSuccessorResponse& other) : HChordMessage()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

HChangeSuccessorResponse::~HChangeSuccessorResponse()
{
    unsigned int i;
}

HChangeSuccessorResponse& HChangeSuccessorResponse::operator=(const HChangeSuccessorResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HChordMessage::operator=(other);
    this->newSuc_var = other.newSuc_var;
    this->newPre_var = other.newPre_var;
    return *this;
}

void HChangeSuccessorResponse::netPack(cCommBuffer *b)
{
    HChordMessage::netPack(b);
    doPacking(b,this->newSuc_var);
    doPacking(b,this->newPre_var);
}

void HChangeSuccessorResponse::netUnpack(cCommBuffer *b)
{
    HChordMessage::netUnpack(b);
    doUnpacking(b,this->newSuc_var);
    doUnpacking(b,this->newPre_var);
}

NodeHandle& HChangeSuccessorResponse::getNewSuc()
{
    return newSuc_var;
}

void HChangeSuccessorResponse::setNewSuc(const NodeHandle& newSuc_var)
{
    this->newSuc_var = newSuc_var;
}

NodeHandle& HChangeSuccessorResponse::getNewPre()
{
    return newPre_var;
}

void HChangeSuccessorResponse::setNewPre(const NodeHandle& newPre_var)
{
    this->newPre_var = newPre_var;
}

class HChangeSuccessorResponseDescriptor : public cClassDescriptor
{
  public:
    HChangeSuccessorResponseDescriptor();
    virtual ~HChangeSuccessorResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(HChangeSuccessorResponseDescriptor);

HChangeSuccessorResponseDescriptor::HChangeSuccessorResponseDescriptor() : cClassDescriptor("HChangeSuccessorResponse", "HChordMessage")
{
}

HChangeSuccessorResponseDescriptor::~HChangeSuccessorResponseDescriptor()
{
}

bool HChangeSuccessorResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<HChangeSuccessorResponse *>(obj)!=NULL;
}

const char *HChangeSuccessorResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HChangeSuccessorResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HChangeSuccessorResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        case 1: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *HChangeSuccessorResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "newSuc";
        case 1: return "newPre";
        default: return NULL;
    }
}

const char *HChangeSuccessorResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        case 1: return "NodeHandle";
        default: return NULL;
    }
}

const char *HChangeSuccessorResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HChangeSuccessorResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorResponse *pp _MAYBEUNUSED = (HChangeSuccessorResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool HChangeSuccessorResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorResponse *pp _MAYBEUNUSED = (HChangeSuccessorResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getNewSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        case 1: {std::stringstream out; out << pp->getNewPre(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool HChangeSuccessorResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorResponse *pp _MAYBEUNUSED = (HChangeSuccessorResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *HChangeSuccessorResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        case 1: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *HChangeSuccessorResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HChangeSuccessorResponse *pp _MAYBEUNUSED = (HChangeSuccessorResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getNewSuc()); break;
        case 1: return (void *)(&pp->getNewPre()); break;
        default: return NULL;
    }
}

Register_Class(UHJoinCall);

UHJoinCall::UHJoinCall(const char *name, int kind) : HJoinCall(name,kind)
{
}

UHJoinCall::UHJoinCall(const UHJoinCall& other) : HJoinCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHJoinCall::~UHJoinCall()
{
    unsigned int i;
}

UHJoinCall& UHJoinCall::operator=(const UHJoinCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HJoinCall::operator=(other);
    this->LowerNewSuc_var = other.LowerNewSuc_var;
    return *this;
}

void UHJoinCall::netPack(cCommBuffer *b)
{
    HJoinCall::netPack(b);
    doPacking(b,this->LowerNewSuc_var);
}

void UHJoinCall::netUnpack(cCommBuffer *b)
{
    HJoinCall::netUnpack(b);
    doUnpacking(b,this->LowerNewSuc_var);
}

NodeHandle& UHJoinCall::getLowerNewSuc()
{
    return LowerNewSuc_var;
}

void UHJoinCall::setLowerNewSuc(const NodeHandle& LowerNewSuc_var)
{
    this->LowerNewSuc_var = LowerNewSuc_var;
}

class UHJoinCallDescriptor : public cClassDescriptor
{
  public:
    UHJoinCallDescriptor();
    virtual ~UHJoinCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHJoinCallDescriptor);

UHJoinCallDescriptor::UHJoinCallDescriptor() : cClassDescriptor("UHJoinCall", "HJoinCall")
{
}

UHJoinCallDescriptor::~UHJoinCallDescriptor()
{
}

bool UHJoinCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHJoinCall *>(obj)!=NULL;
}

const char *UHJoinCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHJoinCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int UHJoinCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *UHJoinCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "LowerNewSuc";
        default: return NULL;
    }
}

const char *UHJoinCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        default: return NULL;
    }
}

const char *UHJoinCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHJoinCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinCall *pp _MAYBEUNUSED = (UHJoinCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHJoinCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinCall *pp _MAYBEUNUSED = (UHJoinCall *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLowerNewSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool UHJoinCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinCall *pp _MAYBEUNUSED = (UHJoinCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHJoinCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *UHJoinCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinCall *pp _MAYBEUNUSED = (UHJoinCall *)object;
    switch (field) {
        case 0: return (void *)(&pp->getLowerNewSuc()); break;
        default: return NULL;
    }
}

Register_Class(UHJoinResponse);

UHJoinResponse::UHJoinResponse(const char *name, int kind) : HJoinResponse(name,kind)
{
}

UHJoinResponse::UHJoinResponse(const UHJoinResponse& other) : HJoinResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHJoinResponse::~UHJoinResponse()
{
    unsigned int i;
}

UHJoinResponse& UHJoinResponse::operator=(const UHJoinResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HJoinResponse::operator=(other);
    this->LowerNewSuc_var = other.LowerNewSuc_var;
    return *this;
}

void UHJoinResponse::netPack(cCommBuffer *b)
{
    HJoinResponse::netPack(b);
    doPacking(b,this->LowerNewSuc_var);
}

void UHJoinResponse::netUnpack(cCommBuffer *b)
{
    HJoinResponse::netUnpack(b);
    doUnpacking(b,this->LowerNewSuc_var);
}

NodeHandle& UHJoinResponse::getLowerNewSuc()
{
    return LowerNewSuc_var;
}

void UHJoinResponse::setLowerNewSuc(const NodeHandle& LowerNewSuc_var)
{
    this->LowerNewSuc_var = LowerNewSuc_var;
}

class UHJoinResponseDescriptor : public cClassDescriptor
{
  public:
    UHJoinResponseDescriptor();
    virtual ~UHJoinResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHJoinResponseDescriptor);

UHJoinResponseDescriptor::UHJoinResponseDescriptor() : cClassDescriptor("UHJoinResponse", "HJoinResponse")
{
}

UHJoinResponseDescriptor::~UHJoinResponseDescriptor()
{
}

bool UHJoinResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHJoinResponse *>(obj)!=NULL;
}

const char *UHJoinResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHJoinResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int UHJoinResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return FD_ISCOMPOUND;
        default: return 0;
    }
}

const char *UHJoinResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "LowerNewSuc";
        default: return NULL;
    }
}

const char *UHJoinResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle";
        default: return NULL;
    }
}

const char *UHJoinResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHJoinResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinResponse *pp _MAYBEUNUSED = (UHJoinResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHJoinResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinResponse *pp _MAYBEUNUSED = (UHJoinResponse *)object;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLowerNewSuc(); opp_strprettytrunc(resultbuf,out.str().c_str(),bufsize-1); return true;}
        default: return false;
    }
}

bool UHJoinResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinResponse *pp _MAYBEUNUSED = (UHJoinResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHJoinResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return "NodeHandle"; break;
        default: return NULL;
    }
}

void *UHJoinResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHJoinResponse *pp _MAYBEUNUSED = (UHJoinResponse *)object;
    switch (field) {
        case 0: return (void *)(&pp->getLowerNewSuc()); break;
        default: return NULL;
    }
}

Register_Class(UHNotifyCall);

UHNotifyCall::UHNotifyCall(const char *name, int kind) : HNotifyCall(name,kind)
{
}

UHNotifyCall::UHNotifyCall(const UHNotifyCall& other) : HNotifyCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHNotifyCall::~UHNotifyCall()
{
    unsigned int i;
}

UHNotifyCall& UHNotifyCall::operator=(const UHNotifyCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HNotifyCall::operator=(other);
    return *this;
}

void UHNotifyCall::netPack(cCommBuffer *b)
{
    HNotifyCall::netPack(b);
}

void UHNotifyCall::netUnpack(cCommBuffer *b)
{
    HNotifyCall::netUnpack(b);
}

class UHNotifyCallDescriptor : public cClassDescriptor
{
  public:
    UHNotifyCallDescriptor();
    virtual ~UHNotifyCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHNotifyCallDescriptor);

UHNotifyCallDescriptor::UHNotifyCallDescriptor() : cClassDescriptor("UHNotifyCall", "HNotifyCall")
{
}

UHNotifyCallDescriptor::~UHNotifyCallDescriptor()
{
}

bool UHNotifyCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHNotifyCall *>(obj)!=NULL;
}

const char *UHNotifyCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHNotifyCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHNotifyCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHNotifyCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNotifyCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNotifyCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHNotifyCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyCall *pp _MAYBEUNUSED = (UHNotifyCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHNotifyCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyCall *pp _MAYBEUNUSED = (UHNotifyCall *)object;
    switch (field) {
        default: return false;
    }
}

bool UHNotifyCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyCall *pp _MAYBEUNUSED = (UHNotifyCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHNotifyCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHNotifyCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyCall *pp _MAYBEUNUSED = (UHNotifyCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHNotifyResponse);

UHNotifyResponse::UHNotifyResponse(const char *name, int kind) : HNotifyResponse(name,kind)
{
}

UHNotifyResponse::UHNotifyResponse(const UHNotifyResponse& other) : HNotifyResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHNotifyResponse::~UHNotifyResponse()
{
    unsigned int i;
}

UHNotifyResponse& UHNotifyResponse::operator=(const UHNotifyResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HNotifyResponse::operator=(other);
    return *this;
}

void UHNotifyResponse::netPack(cCommBuffer *b)
{
    HNotifyResponse::netPack(b);
}

void UHNotifyResponse::netUnpack(cCommBuffer *b)
{
    HNotifyResponse::netUnpack(b);
}

class UHNotifyResponseDescriptor : public cClassDescriptor
{
  public:
    UHNotifyResponseDescriptor();
    virtual ~UHNotifyResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHNotifyResponseDescriptor);

UHNotifyResponseDescriptor::UHNotifyResponseDescriptor() : cClassDescriptor("UHNotifyResponse", "HNotifyResponse")
{
}

UHNotifyResponseDescriptor::~UHNotifyResponseDescriptor()
{
}

bool UHNotifyResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHNotifyResponse *>(obj)!=NULL;
}

const char *UHNotifyResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHNotifyResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHNotifyResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHNotifyResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNotifyResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNotifyResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHNotifyResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyResponse *pp _MAYBEUNUSED = (UHNotifyResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHNotifyResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyResponse *pp _MAYBEUNUSED = (UHNotifyResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool UHNotifyResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyResponse *pp _MAYBEUNUSED = (UHNotifyResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHNotifyResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHNotifyResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHNotifyResponse *pp _MAYBEUNUSED = (UHNotifyResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHStabilizeCall);

UHStabilizeCall::UHStabilizeCall(const char *name, int kind) : HStabilizeCall(name,kind)
{
}

UHStabilizeCall::UHStabilizeCall(const UHStabilizeCall& other) : HStabilizeCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHStabilizeCall::~UHStabilizeCall()
{
    unsigned int i;
}

UHStabilizeCall& UHStabilizeCall::operator=(const UHStabilizeCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HStabilizeCall::operator=(other);
    return *this;
}

void UHStabilizeCall::netPack(cCommBuffer *b)
{
    HStabilizeCall::netPack(b);
}

void UHStabilizeCall::netUnpack(cCommBuffer *b)
{
    HStabilizeCall::netUnpack(b);
}

class UHStabilizeCallDescriptor : public cClassDescriptor
{
  public:
    UHStabilizeCallDescriptor();
    virtual ~UHStabilizeCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHStabilizeCallDescriptor);

UHStabilizeCallDescriptor::UHStabilizeCallDescriptor() : cClassDescriptor("UHStabilizeCall", "HStabilizeCall")
{
}

UHStabilizeCallDescriptor::~UHStabilizeCallDescriptor()
{
}

bool UHStabilizeCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHStabilizeCall *>(obj)!=NULL;
}

const char *UHStabilizeCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHStabilizeCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHStabilizeCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHStabilizeCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHStabilizeCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHStabilizeCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHStabilizeCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeCall *pp _MAYBEUNUSED = (UHStabilizeCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHStabilizeCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeCall *pp _MAYBEUNUSED = (UHStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

bool UHStabilizeCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeCall *pp _MAYBEUNUSED = (UHStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHStabilizeCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHStabilizeCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeCall *pp _MAYBEUNUSED = (UHStabilizeCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHStabilizeResponse);

UHStabilizeResponse::UHStabilizeResponse(const char *name, int kind) : HStabilizeResponse(name,kind)
{
}

UHStabilizeResponse::UHStabilizeResponse(const UHStabilizeResponse& other) : HStabilizeResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHStabilizeResponse::~UHStabilizeResponse()
{
    unsigned int i;
}

UHStabilizeResponse& UHStabilizeResponse::operator=(const UHStabilizeResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HStabilizeResponse::operator=(other);
    return *this;
}

void UHStabilizeResponse::netPack(cCommBuffer *b)
{
    HStabilizeResponse::netPack(b);
}

void UHStabilizeResponse::netUnpack(cCommBuffer *b)
{
    HStabilizeResponse::netUnpack(b);
}

class UHStabilizeResponseDescriptor : public cClassDescriptor
{
  public:
    UHStabilizeResponseDescriptor();
    virtual ~UHStabilizeResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHStabilizeResponseDescriptor);

UHStabilizeResponseDescriptor::UHStabilizeResponseDescriptor() : cClassDescriptor("UHStabilizeResponse", "HStabilizeResponse")
{
}

UHStabilizeResponseDescriptor::~UHStabilizeResponseDescriptor()
{
}

bool UHStabilizeResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHStabilizeResponse *>(obj)!=NULL;
}

const char *UHStabilizeResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHStabilizeResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHStabilizeResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHStabilizeResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHStabilizeResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHStabilizeResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHStabilizeResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeResponse *pp _MAYBEUNUSED = (UHStabilizeResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHStabilizeResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeResponse *pp _MAYBEUNUSED = (UHStabilizeResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool UHStabilizeResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeResponse *pp _MAYBEUNUSED = (UHStabilizeResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHStabilizeResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHStabilizeResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHStabilizeResponse *pp _MAYBEUNUSED = (UHStabilizeResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHFixfingersCall);

UHFixfingersCall::UHFixfingersCall(const char *name, int kind) : HFixfingersCall(name,kind)
{
}

UHFixfingersCall::UHFixfingersCall(const UHFixfingersCall& other) : HFixfingersCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHFixfingersCall::~UHFixfingersCall()
{
    unsigned int i;
}

UHFixfingersCall& UHFixfingersCall::operator=(const UHFixfingersCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HFixfingersCall::operator=(other);
    return *this;
}

void UHFixfingersCall::netPack(cCommBuffer *b)
{
    HFixfingersCall::netPack(b);
}

void UHFixfingersCall::netUnpack(cCommBuffer *b)
{
    HFixfingersCall::netUnpack(b);
}

class UHFixfingersCallDescriptor : public cClassDescriptor
{
  public:
    UHFixfingersCallDescriptor();
    virtual ~UHFixfingersCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHFixfingersCallDescriptor);

UHFixfingersCallDescriptor::UHFixfingersCallDescriptor() : cClassDescriptor("UHFixfingersCall", "HFixfingersCall")
{
}

UHFixfingersCallDescriptor::~UHFixfingersCallDescriptor()
{
}

bool UHFixfingersCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHFixfingersCall *>(obj)!=NULL;
}

const char *UHFixfingersCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHFixfingersCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHFixfingersCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHFixfingersCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHFixfingersCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHFixfingersCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHFixfingersCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersCall *pp _MAYBEUNUSED = (UHFixfingersCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHFixfingersCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersCall *pp _MAYBEUNUSED = (UHFixfingersCall *)object;
    switch (field) {
        default: return false;
    }
}

bool UHFixfingersCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersCall *pp _MAYBEUNUSED = (UHFixfingersCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHFixfingersCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHFixfingersCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersCall *pp _MAYBEUNUSED = (UHFixfingersCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHFixfingersResponse);

UHFixfingersResponse::UHFixfingersResponse(const char *name, int kind) : HFixfingersResponse(name,kind)
{
}

UHFixfingersResponse::UHFixfingersResponse(const UHFixfingersResponse& other) : HFixfingersResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHFixfingersResponse::~UHFixfingersResponse()
{
    unsigned int i;
}

UHFixfingersResponse& UHFixfingersResponse::operator=(const UHFixfingersResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HFixfingersResponse::operator=(other);
    return *this;
}

void UHFixfingersResponse::netPack(cCommBuffer *b)
{
    HFixfingersResponse::netPack(b);
}

void UHFixfingersResponse::netUnpack(cCommBuffer *b)
{
    HFixfingersResponse::netUnpack(b);
}

class UHFixfingersResponseDescriptor : public cClassDescriptor
{
  public:
    UHFixfingersResponseDescriptor();
    virtual ~UHFixfingersResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHFixfingersResponseDescriptor);

UHFixfingersResponseDescriptor::UHFixfingersResponseDescriptor() : cClassDescriptor("UHFixfingersResponse", "HFixfingersResponse")
{
}

UHFixfingersResponseDescriptor::~UHFixfingersResponseDescriptor()
{
}

bool UHFixfingersResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHFixfingersResponse *>(obj)!=NULL;
}

const char *UHFixfingersResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHFixfingersResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHFixfingersResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHFixfingersResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHFixfingersResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHFixfingersResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHFixfingersResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersResponse *pp _MAYBEUNUSED = (UHFixfingersResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHFixfingersResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersResponse *pp _MAYBEUNUSED = (UHFixfingersResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool UHFixfingersResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersResponse *pp _MAYBEUNUSED = (UHFixfingersResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHFixfingersResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHFixfingersResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHFixfingersResponse *pp _MAYBEUNUSED = (UHFixfingersResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UHNewSuccessorHintMsg);

UHNewSuccessorHintMsg::UHNewSuccessorHintMsg(const char *name, int kind) : HNewSuccessorHintMsg(name,kind)
{
}

UHNewSuccessorHintMsg::UHNewSuccessorHintMsg(const UHNewSuccessorHintMsg& other) : HNewSuccessorHintMsg()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

UHNewSuccessorHintMsg::~UHNewSuccessorHintMsg()
{
    unsigned int i;
}

UHNewSuccessorHintMsg& UHNewSuccessorHintMsg::operator=(const UHNewSuccessorHintMsg& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HNewSuccessorHintMsg::operator=(other);
    return *this;
}

void UHNewSuccessorHintMsg::netPack(cCommBuffer *b)
{
    HNewSuccessorHintMsg::netPack(b);
}

void UHNewSuccessorHintMsg::netUnpack(cCommBuffer *b)
{
    HNewSuccessorHintMsg::netUnpack(b);
}

class UHNewSuccessorHintMsgDescriptor : public cClassDescriptor
{
  public:
    UHNewSuccessorHintMsgDescriptor();
    virtual ~UHNewSuccessorHintMsgDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(UHNewSuccessorHintMsgDescriptor);

UHNewSuccessorHintMsgDescriptor::UHNewSuccessorHintMsgDescriptor() : cClassDescriptor("UHNewSuccessorHintMsg", "HNewSuccessorHintMsg")
{
}

UHNewSuccessorHintMsgDescriptor::~UHNewSuccessorHintMsgDescriptor()
{
}

bool UHNewSuccessorHintMsgDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<UHNewSuccessorHintMsg *>(obj)!=NULL;
}

const char *UHNewSuccessorHintMsgDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UHNewSuccessorHintMsgDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UHNewSuccessorHintMsgDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *UHNewSuccessorHintMsgDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNewSuccessorHintMsgDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *UHNewSuccessorHintMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UHNewSuccessorHintMsgDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UHNewSuccessorHintMsg *pp _MAYBEUNUSED = (UHNewSuccessorHintMsg *)object;
    switch (field) {
        default: return 0;
    }
}

bool UHNewSuccessorHintMsgDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    UHNewSuccessorHintMsg *pp _MAYBEUNUSED = (UHNewSuccessorHintMsg *)object;
    switch (field) {
        default: return false;
    }
}

bool UHNewSuccessorHintMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UHNewSuccessorHintMsg *pp _MAYBEUNUSED = (UHNewSuccessorHintMsg *)object;
    switch (field) {
        default: return false;
    }
}

const char *UHNewSuccessorHintMsgDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *UHNewSuccessorHintMsgDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UHNewSuccessorHintMsg *pp _MAYBEUNUSED = (UHNewSuccessorHintMsg *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LHStabilizeCall);

LHStabilizeCall::LHStabilizeCall(const char *name, int kind) : HStabilizeCall(name,kind)
{
}

LHStabilizeCall::LHStabilizeCall(const LHStabilizeCall& other) : HStabilizeCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

LHStabilizeCall::~LHStabilizeCall()
{
    unsigned int i;
}

LHStabilizeCall& LHStabilizeCall::operator=(const LHStabilizeCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HStabilizeCall::operator=(other);
    return *this;
}

void LHStabilizeCall::netPack(cCommBuffer *b)
{
    HStabilizeCall::netPack(b);
}

void LHStabilizeCall::netUnpack(cCommBuffer *b)
{
    HStabilizeCall::netUnpack(b);
}

class LHStabilizeCallDescriptor : public cClassDescriptor
{
  public:
    LHStabilizeCallDescriptor();
    virtual ~LHStabilizeCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(LHStabilizeCallDescriptor);

LHStabilizeCallDescriptor::LHStabilizeCallDescriptor() : cClassDescriptor("LHStabilizeCall", "HStabilizeCall")
{
}

LHStabilizeCallDescriptor::~LHStabilizeCallDescriptor()
{
}

bool LHStabilizeCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<LHStabilizeCall *>(obj)!=NULL;
}

const char *LHStabilizeCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LHStabilizeCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int LHStabilizeCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *LHStabilizeCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHStabilizeCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHStabilizeCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LHStabilizeCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeCall *pp _MAYBEUNUSED = (LHStabilizeCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool LHStabilizeCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeCall *pp _MAYBEUNUSED = (LHStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

bool LHStabilizeCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeCall *pp _MAYBEUNUSED = (LHStabilizeCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *LHStabilizeCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *LHStabilizeCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeCall *pp _MAYBEUNUSED = (LHStabilizeCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LHStabilizeResponse);

LHStabilizeResponse::LHStabilizeResponse(const char *name, int kind) : HStabilizeResponse(name,kind)
{
}

LHStabilizeResponse::LHStabilizeResponse(const LHStabilizeResponse& other) : HStabilizeResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

LHStabilizeResponse::~LHStabilizeResponse()
{
    unsigned int i;
}

LHStabilizeResponse& LHStabilizeResponse::operator=(const LHStabilizeResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HStabilizeResponse::operator=(other);
    return *this;
}

void LHStabilizeResponse::netPack(cCommBuffer *b)
{
    HStabilizeResponse::netPack(b);
}

void LHStabilizeResponse::netUnpack(cCommBuffer *b)
{
    HStabilizeResponse::netUnpack(b);
}

class LHStabilizeResponseDescriptor : public cClassDescriptor
{
  public:
    LHStabilizeResponseDescriptor();
    virtual ~LHStabilizeResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(LHStabilizeResponseDescriptor);

LHStabilizeResponseDescriptor::LHStabilizeResponseDescriptor() : cClassDescriptor("LHStabilizeResponse", "HStabilizeResponse")
{
}

LHStabilizeResponseDescriptor::~LHStabilizeResponseDescriptor()
{
}

bool LHStabilizeResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<LHStabilizeResponse *>(obj)!=NULL;
}

const char *LHStabilizeResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LHStabilizeResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int LHStabilizeResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *LHStabilizeResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHStabilizeResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHStabilizeResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LHStabilizeResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeResponse *pp _MAYBEUNUSED = (LHStabilizeResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool LHStabilizeResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeResponse *pp _MAYBEUNUSED = (LHStabilizeResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool LHStabilizeResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeResponse *pp _MAYBEUNUSED = (LHStabilizeResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *LHStabilizeResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *LHStabilizeResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LHStabilizeResponse *pp _MAYBEUNUSED = (LHStabilizeResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LHFixfingersCall);

LHFixfingersCall::LHFixfingersCall(const char *name, int kind) : UHFixfingersCall(name,kind)
{
}

LHFixfingersCall::LHFixfingersCall(const LHFixfingersCall& other) : UHFixfingersCall()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

LHFixfingersCall::~LHFixfingersCall()
{
    unsigned int i;
}

LHFixfingersCall& LHFixfingersCall::operator=(const LHFixfingersCall& other)
{
    if (this==&other) return *this;
    unsigned int i;
    UHFixfingersCall::operator=(other);
    return *this;
}

void LHFixfingersCall::netPack(cCommBuffer *b)
{
    UHFixfingersCall::netPack(b);
}

void LHFixfingersCall::netUnpack(cCommBuffer *b)
{
    UHFixfingersCall::netUnpack(b);
}

class LHFixfingersCallDescriptor : public cClassDescriptor
{
  public:
    LHFixfingersCallDescriptor();
    virtual ~LHFixfingersCallDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(LHFixfingersCallDescriptor);

LHFixfingersCallDescriptor::LHFixfingersCallDescriptor() : cClassDescriptor("LHFixfingersCall", "UHFixfingersCall")
{
}

LHFixfingersCallDescriptor::~LHFixfingersCallDescriptor()
{
}

bool LHFixfingersCallDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<LHFixfingersCall *>(obj)!=NULL;
}

const char *LHFixfingersCallDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LHFixfingersCallDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int LHFixfingersCallDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *LHFixfingersCallDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHFixfingersCallDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHFixfingersCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LHFixfingersCallDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersCall *pp _MAYBEUNUSED = (LHFixfingersCall *)object;
    switch (field) {
        default: return 0;
    }
}

bool LHFixfingersCallDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersCall *pp _MAYBEUNUSED = (LHFixfingersCall *)object;
    switch (field) {
        default: return false;
    }
}

bool LHFixfingersCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersCall *pp _MAYBEUNUSED = (LHFixfingersCall *)object;
    switch (field) {
        default: return false;
    }
}

const char *LHFixfingersCallDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *LHFixfingersCallDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersCall *pp _MAYBEUNUSED = (LHFixfingersCall *)object;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(LHFixfingersResponse);

LHFixfingersResponse::LHFixfingersResponse(const char *name, int kind) : HFixfingersResponse(name,kind)
{
}

LHFixfingersResponse::LHFixfingersResponse(const LHFixfingersResponse& other) : HFixfingersResponse()
{
    unsigned int i;
    setName(other.name());
    operator=(other);
}

LHFixfingersResponse::~LHFixfingersResponse()
{
    unsigned int i;
}

LHFixfingersResponse& LHFixfingersResponse::operator=(const LHFixfingersResponse& other)
{
    if (this==&other) return *this;
    unsigned int i;
    HFixfingersResponse::operator=(other);
    return *this;
}

void LHFixfingersResponse::netPack(cCommBuffer *b)
{
    HFixfingersResponse::netPack(b);
}

void LHFixfingersResponse::netUnpack(cCommBuffer *b)
{
    HFixfingersResponse::netUnpack(b);
}

class LHFixfingersResponseDescriptor : public cClassDescriptor
{
  public:
    LHFixfingersResponseDescriptor();
    virtual ~LHFixfingersResponseDescriptor();

    virtual bool doesSupport(cPolymorphic *obj);
    virtual const char *getProperty(const char *propertyname);
    virtual int getFieldCount(void *object);
    virtual const char *getFieldName(void *object, int field);
    virtual unsigned int getFieldTypeFlags(void *object, int field);
    virtual const char *getFieldTypeString(void *object, int field);
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname);
    virtual int getArraySize(void *object, int field);

    virtual bool getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize);
    virtual bool setFieldAsString(void *object, int field, int i, const char *value);

    virtual const char *getFieldStructName(void *object, int field);
    virtual void *getFieldStructPointer(void *object, int field, int i);
};

Register_ClassDescriptor(LHFixfingersResponseDescriptor);

LHFixfingersResponseDescriptor::LHFixfingersResponseDescriptor() : cClassDescriptor("LHFixfingersResponse", "HFixfingersResponse")
{
}

LHFixfingersResponseDescriptor::~LHFixfingersResponseDescriptor()
{
}

bool LHFixfingersResponseDescriptor::doesSupport(cPolymorphic *obj)
{
    return dynamic_cast<LHFixfingersResponse *>(obj)!=NULL;
}

const char *LHFixfingersResponseDescriptor::getProperty(const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LHFixfingersResponseDescriptor::getFieldCount(void *object)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int LHFixfingersResponseDescriptor::getFieldTypeFlags(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return 0;
    }
}

const char *LHFixfingersResponseDescriptor::getFieldName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHFixfingersResponseDescriptor::getFieldTypeString(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

const char *LHFixfingersResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LHFixfingersResponseDescriptor::getArraySize(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersResponse *pp _MAYBEUNUSED = (LHFixfingersResponse *)object;
    switch (field) {
        default: return 0;
    }
}

bool LHFixfingersResponseDescriptor::getFieldAsString(void *object, int field, int i, char *resultbuf, int bufsize)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i,resultbuf,bufsize);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersResponse *pp _MAYBEUNUSED = (LHFixfingersResponse *)object;
    switch (field) {
        default: return false;
    }
}

bool LHFixfingersResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersResponse *pp _MAYBEUNUSED = (LHFixfingersResponse *)object;
    switch (field) {
        default: return false;
    }
}

const char *LHFixfingersResponseDescriptor::getFieldStructName(void *object, int field)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

void *LHFixfingersResponseDescriptor::getFieldStructPointer(void *object, int field, int i)
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LHFixfingersResponse *pp _MAYBEUNUSED = (LHFixfingersResponse *)object;
    switch (field) {
        default: return NULL;
    }
}

