namespace Shiboken {
template<typename FT, typename ST>
struct Converter<QPair<FT, ST> > : StdPairConverter<QPair<FT, ST> > {};
}
