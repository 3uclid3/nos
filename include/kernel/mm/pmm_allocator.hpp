#pragma once

#include <cstddef>

#include <coal/alignment.hpp>
#include <coal/memory_block.hpp>

namespace nos {

class pmm;

class pmm_allocator
{
public:
    static constexpr std::size_t alignment = coal::default_alignment;

    constexpr std::size_t get_alignment() const;

    template<typename Initializer>
    void init(Initializer& initializer);

    [[nodiscard]] bool owns(const coal::memory_block& block) const;
    [[nodiscard]] coal::memory_block allocate(std::size_t size);
    bool reallocate(coal::memory_block& block, std::size_t new_size);
    void deallocate(coal::memory_block& block);

    void set_pmm(pmm& pmm_) { _pmm = &pmm_; }

private:
    pmm* _pmm{nullptr};
};

constexpr std::size_t pmm_allocator::get_alignment() const
{
    return alignment;
}

template<typename Initializer>
void pmm_allocator::init(Initializer& initializer)
{
    initializer.init(*this);
}

} // namespace nos