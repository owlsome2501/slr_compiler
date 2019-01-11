#ifndef SEM
#define SEM

#include <memory>
#include <vector>
#include "sem_patch.h"

struct sem_unit;
typedef std::shared_ptr<sem_unit> su_ptr;
typedef std::shared_ptr<std::vector<su_ptr>> su_list;
struct sem_unit {
	sem type;
	std::string text;
	unsigned uint;
	su_list args;
};

#endif
