namespace Shiboken {
template<typename T>
struct Converter<QStack<T> > : StdListConverter<QStack<T> > {};
}
