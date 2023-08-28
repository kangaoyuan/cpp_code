#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <ostream>
#include <tuple>
#include <utility>
#include <iostream>
#include <type_traits>


template<typename T>
struct is_pair: std::false_type {};
template<typename T, typename U>
struct is_pair<std::pair<T, U>>: std::true_type {};

template<typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;

enum class char_type{
    Char,
    String,
    Others
};

template<typename T>
std::ostream& output_element(std::ostream& os, const T& elem);

template<typename T, typename U>
std::ostream& output_element(std::ostream& os, const std::pair<T,U>& elem);

template<typename... T, size_t... I>
std::ostream& output_element(std::ostream& os, const std::tuple<T...>& tuple_obj, std::index_sequence<I...> index_seq);

template<typename T, typename U>
decltype(auto) operator<< (std::ostream& os, const std::pair<T, U>& pair_obj);

template<typename... T>
std::ostream& operator<< (std::ostream& os, const std::tuple<T...>& tuple_obj);

template <typename T, typename>
auto operator<< (std::ostream& os, const T& container) 
-> decltype(container.size(), container.begin(), container.end(), os);


template<typename T>
struct has_output {
    template<typename U>
    constexpr static auto output(U* ptr)
    //-> decltype(std::declval<std::ostream&>() << *ptr, true) {
    -> decltype(std::declval<std::ostream&>() << std::declval<U>(), true) {
        return true;  
    }
    
    template<typename U>
    constexpr static auto output(...) { return false; }

    constexpr static bool value = output<T>(nullptr);
};

template<typename T>
constexpr inline bool has_output_v = has_output<T>::value;

template<typename T>
char_type is_char(const T& elem) {
    if constexpr(std::is_same_v<char, std::decay_t<decltype(elem)> >){
        return char_type::Char; 
    } else if constexpr(std::is_same_v<std::string, std::decay_t<decltype(elem)>>) {
        return char_type::String;
    } else {
        return char_type::Others; 
    }
}

/* For std::pair<T, U> object output */
template<typename T, typename U>
decltype(auto) operator<< (std::ostream& os, const std::pair<T, U>& pair_obj) {
    os << "(" << pair_obj.first << ", " << pair_obj.second << ")";
    return os;
}

template<typename... T>
std::ostream& operator<< (std::ostream& os, const std::tuple<T...>& tuple_obj){
    os << "(";
    constexpr size_t size = std::tuple_size_v<decltype(tuple_obj)>;
    output_element(os, tuple_obj, std::make_index_sequence<size>{});
    os << ")";
    return os;
}

/* For containers output, which need define begin() and end() member functions.
 * Also checking container whether already defining operator<< */
template <typename T, typename = std::enable_if_t<!has_output_v<T>>>
auto operator<< (std::ostream& os, const T& container) 
-> decltype(container.size(), container.begin(), container.end(), os) {
    auto start = container.begin();
    size_t size = container.size();
    using elem_type = std::decay_t<decltype(*start)>;
    constexpr bool is_char_elem = std::is_same_v<char, elem_type>;
    if constexpr (!is_char_elem) {
        os << "{ "; 
        // No need to judge whether is empty? because size 
        if(size >= 1){
            output_element(os, *start++);
        }
        for(size_t i = 1; i < size; i++){
            os << ", ";
            output_element(os, *start++);
        }
        os << " }"; 
    } else {
        for(size_t i = 0; i < size; i++){
            if(*start == '\0'){
                break; 
            }
            output_element(os, *start++); 
        }
    }
    return os;
}

template<typename T>
std::ostream& output_element(std::ostream& os, const T& elem){
    using elem_type = std::decay_t<decltype(elem)>;
    constexpr bool is_char_elem = std::is_same_v<char, elem_type>;
    /* Attention std::decay_t<> doesn't decay the low-level const */
    constexpr bool is_str_elem = std::is_same_v<char*, elem_type> || std::is_same_v<const char*, elem_type>  || std::is_same_v<std::string, elem_type>;
    if constexpr(is_char_elem) {
        os << "'" << elem << "'";
    } else if constexpr(is_str_elem) {
        os << '"' << elem << '"'; 
    }
    else {
        os << elem; 
    }
    return os;
}

template<typename T, typename U>
std::ostream& output_element(std::ostream& os, const std::pair<T,U>& elem){
    output_element(os, elem.first);
    os << " => ";
    output_element(os, elem.second);
    //os << elem.first << " => " << elem.second; 
    return os;
}

// Don't need do it, because this output_element function only called in operator<<, which has constraints about .begin() and so on member functions.
template<typename T, typename V>
auto _ouput_element(std::ostream& os, const T& element, const V& container)
-> decltype(std::declval<typename V::key_type>(), is_pair_v<V>, os){
    os << element.first << " => " << element.second;
    return os;
}

template<typename... T, size_t... I>
std::ostream& output_element(std::ostream& os, const std::tuple<T...>& tuple_obj, std::index_sequence<I...> index_seq){
    if(sizeof...(I) >= 1){
        os << std::get<0>(tuple_obj); 
    }
    (((os << ( I == 0  ? ""  : ", ")) << std::get<I>(tuple_obj)), ...);
    return os; 
}

#endif
