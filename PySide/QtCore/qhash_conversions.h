namespace Shiboken {
template<typename KT, typename VT>
struct Converter<QHash<KT, VT> > : QtDictConverter<QHash<KT, VT> > {};
}
