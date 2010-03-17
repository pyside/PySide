namespace Shiboken {
template<typename T>
struct Converter<QSet<T> > : QSequenceConverter<QSet<T> > {};
}
