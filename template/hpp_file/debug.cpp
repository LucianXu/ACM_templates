tandu std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << '<' << p.ff << ',' << p.ss << '>';
}

template <
    typet, typename = decltype(std::begin(std::declval<T>())),
    typename = std::enable_if_t<!std::is_same_v<T, std::string>>>
std::ostream& operator<<(std::ostream& os, const T& c) {
    auto it = std::begin(c);
    if (it == std::end(c)) return os << "{}";
    for (os << '{' << *it; ++it != std::end(c); os << ',' << *it)
        ;
    return os << '}';
}

#define debug(arg...)                \
    do {                             \
        std::cerr << "[" #arg "] :"; \
        dbg(arg);                    \
    } while (false)

temps void dbg(Ts... args) {
    (..., (std::cerr << ' ' << args));
    std::cerr << endl;
}
