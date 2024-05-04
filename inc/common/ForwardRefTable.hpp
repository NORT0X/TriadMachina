#include <vector>
#include <cstdint>

typedef uint32_t ForwardRefIndex;

struct ForwardRefEntry;

class ForwardRefTable
{
public:
    void addForwardRef(ForwardRefEntry entry);
    ForwardRefEntry *findForwardRef(ForwardRefIndex index);

private:
    std::vector<ForwardRefEntry> table;
};