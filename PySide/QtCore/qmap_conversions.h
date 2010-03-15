namespace Shiboken {
template<typename KT, typename VT>
struct Converter<QMap<KT, VT> > : QtDictConverter<QMap<KT, VT> > {
};
}
