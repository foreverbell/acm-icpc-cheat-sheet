#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// order_of_key :: T -> size_t
// find_by_order :: size_t -> iterator, analogy to lower_bound
// use null_mapped_type instead of null_type if G++ version < 4.7.0
template <typename T> using hyperset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename U> using hypermap = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
