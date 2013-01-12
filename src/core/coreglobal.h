#ifndef QTXCORE_GLOBAL_H
#define QTXCORE_GLOBAL_H

#ifndef QTX_NAMESPACE
#  define QTX_NAMESPACE Qtx
#endif
#ifndef QTX_USE_NAMESPACE
#  define QTX_USE_NAMESPACE using namespace ::QTX_NAMESPACE;
#endif
#ifndef QTX_BEGIN_NAMESPACE
#  define QTX_BEGIN_NAMESPACE namespace QTX_NAMESPACE {
#endif
#ifndef QTX_END_NAMESPACE
#  define QTX_END_NAMESPACE }
#endif


#define QTX_METHOD(s) QMetaObject::normalizedSignature(#s)


#endif /* QTXCORE_GLOBAL_H */
