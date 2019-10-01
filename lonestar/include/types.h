#ifndef TYPES_H
#define TYPES_H

#include "galois/Bag.h"
#include "galois/Galois.h"
#include "galois/substrate/PerThreadStorage.h"
#include "galois/substrate/SimpleLock.h"

typedef float Weight;
typedef unsigned IndexTy;
typedef unsigned VertexId;
typedef unsigned char BYTE;
typedef unsigned long Ulong;
typedef galois::gstl::Vector<BYTE> ByteList;
typedef galois::gstl::Vector<unsigned> UintList;
typedef galois::gstl::Vector<Ulong> UlongList;
typedef galois::gstl::Vector<VertexId> VertexList;
typedef galois::gstl::Vector<UintList> IndexLists;
typedef galois::gstl::Vector<ByteList> ByteLists;
typedef galois::gstl::Vector<VertexList> VertexLists;
typedef galois::gstl::Set<VertexId> VertexSet;
typedef galois::substrate::PerThreadStorage<UintList> Lists;

// We provide two types of 'support': frequency and domain support.
// Frequency is used for counting, e.g. motif counting.
// Domain support, a.k.a, the minimum image-based support, is used for FSM. It has the anti-monotonic property.
typedef float MatType;
typedef unsigned Frequency;
typedef std::vector<std::vector<MatType> > Matrix;
typedef galois::GAccumulator<unsigned> UintAccu;
typedef galois::GAccumulator<unsigned long> UlongAccu;
typedef std::unordered_map<unsigned, unsigned> UintMap;
typedef galois::substrate::PerThreadStorage<UintMap> LocalUintMap;

typedef std::pair<unsigned, unsigned> InitPattern;
typedef std::unordered_map<unsigned, unsigned> FreqMap;
typedef std::unordered_map<unsigned, bool> DomainMap;
//typedef galois::gstl::Map<unsigned, unsigned> FreqMap;
//typedef galois::gstl::UnorderedMap<unsigned, bool> DomainMap;

struct Edge {
	VertexId src;
	VertexId dst;
#ifdef USE_DOMAIN
	unsigned src_domain;
	unsigned dst_domain;
	Edge(VertexId _src, VertexId _dst, unsigned _src_domain, unsigned _dst_domain) : src(_src), dst(_dst), src_domain(_src_domain), dst_domain(_dst_domain) {}
#endif
	Edge(VertexId _src, VertexId _dst) : src(_src), dst(_dst) {}
	Edge() : src(0), dst(0) {}
	~Edge() {}
	std::string toString() {
		return "(" + std::to_string(src) + ", " + std::to_string(dst) + ")";
	}
	std::string to_string() const {
		std::stringstream ss;
		ss << "e(" << src << "," << dst << "," << ")";
		return ss.str();
	}
	void swap() {
		if (src > dst) {
			VertexId tmp = src;
			src = dst;
			dst = tmp;
#ifdef USE_DOMAIN
			unsigned domain = src_domain;
			src_domain = dst_domain;
			dst_domain = domain;
#endif
		}
	}
};

#endif
