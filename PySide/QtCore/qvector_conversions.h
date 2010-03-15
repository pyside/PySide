namespace Shiboken {
template<typename T>
struct Converter<QVector<T> > : StdListConverter<QVector<T> > {};
}
