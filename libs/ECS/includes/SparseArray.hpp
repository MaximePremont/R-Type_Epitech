/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Sparse_array
*/

#pragma once

#include <optional>
#include <vector>

namespace ECS {
    template <typename Component>
    class SparseArray {
        public:
            using value_type = std::optional<Component>;
            using reference_type = value_type &;
            using const_reference_type = value_type const &;
            using container = std::vector<value_type>;
            using size_type = typename container::size_type;
            using iterator = typename container::iterator;
            using const_iterator = typename container::const_iterator;

            /**
             * Usable operator
             * 
             * @param idx Container index
             * @return Reference type
             */
            reference_type operator[](std::size_t const idx) {
                return _container[idx];
            }
            /**
             * Usable operator
             * 
             * @param idx Container index
             * @return Const reference type
             */
            const_reference_type operator[](std::size_t const idx) const {
                return const_cast<reference_type>(_container[idx]);
            }

            /**
             * Get begin of container iterator
             * 
             * @return Container iterator
             */
            iterator iterator_begin() {
                return _container.begin();
            }
            /**
             * Get begin of container iterator
             * 
             * @return Const container iterator
             */
            const_iterator const_iterator_begin() const {
                return _container.begin();
            }

            /**
             * Get end of container iterator
             * 
             * @return Container iterator
             */
            iterator iterator_end() {
                return _container.end();
            }
            /**
             * Get end of container iterator
             * 
             * @return Const container iterator
             */
            const_iterator const_iterator_end() const {
                return _container.end();
            }

            /**
             * Get container size
             * 
             * @return Container size
             */
            std::size_t size() const {
                return _container.size();
            }

            /**
             * Component insertion
             * 
             * Insert an optional component in the container.
             * 
             * @param component Optional component
             * @return Reference type
             */
            reference_type insert(std::optional<Component> component) {
                _container.push_back(component);
                return _container[_container.size() - 1];
            }

            /**
             * Component erasure
             * 
             * Erase a component at a specific position, this function define case to
             * nullopt and not delete it.
             * 
             * @param pos Component postion
             */
            void erase(size_type const pos) {
                _container[pos] = std::nullopt;
            }
        private:
            container _container;
    };
}
