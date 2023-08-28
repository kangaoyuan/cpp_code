// This is template declaration, not definition.
template<bool>
struct compile_time_error;

template<>
struct compile_time_error<true>{};

// If Eexpr is false, comile_time_error<false> will casue compile failure. because it's never been defined.
#define STATIC_ASSERT(Expr, Msg)    {\
    compile_time_error<bool(Expr)>  \
    (void)ERROR_##_Msg;             \
} 

// Although this is template definition, but using specializatin difference.
template<bool Cond, typename Type=void>
class enable_if {};

template<typename Type>
class enable_if <true, Type>{
public:
    using type = Type;
};

template<typename T, T Value>
struct integral_constant {
    static constexpr T value = Value;
};

template<auto Value>
struct constant {
    static constexpr auto value = Value;
};

template<bool Value>
using bool_constant = integral_constant<bool, Value>;

// two auto usages 
template<auto Arg>
struct AtuoExample{
    // static constexpr default is inline
    static constexpr auto value = Arg;
};

// Three catgories of template argument.
// Non-type template argument must be assigned to a literal type value.
template<
auto K,
typename T,
template <typename U, typename V> class Container>
class Example {};
