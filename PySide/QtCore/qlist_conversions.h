namespace Shiboken {
template<typename T>
struct Converter<QList<T> > : StdListConverter<QList<T> > {};
}
