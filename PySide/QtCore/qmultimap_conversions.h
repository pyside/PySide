namespace Shiboken {
template<typename KT, typename VT>
struct Converter<QMultiMap<KT, VT> > : QtMultiMapConverter<QMap<KT, VT> > {
};
}
