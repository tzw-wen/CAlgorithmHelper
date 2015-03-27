/*
 * Copyright 2015 ZHIHUI WEN (tzw.wen@gmail.com)

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SORTHELPER_H__
#define __SORTHELPER_H__

#pragma once
///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class Pred = std::less<T1> >
#else
template<class T1, class Pred = std::less<T1> >
#endif
struct sort_complex_by_real {
    bool operator()(const std::complex<T1>&left, const std::complex<T1>&right) {
        Pred p;
        return p(left.real(), right.real());
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class Pred = std::less<T1> >
#else
template<class T1, class Pred = std::less<T1> >
#endif
struct sort_complex_by_imag {
    bool operator()(const std::complex<T1>&left, const std::complex<T1>&right) {
        Pred p;
        return p(left.imag(), right.imag());
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class T2, class Pred = std::less<T1> >
#else
template<class T1, class T2, class Pred = std::less<T1> >
#endif
struct sort_pair_by_first {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.first, right.first);
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class T2, class Pred = std::less<T2> >
#else
template<class T1, class T2, class Pred = std::less<T2> >
#endif
struct sort_pair_by_second {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.second, right.second);
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
template<template <typename> class P = std::less >
struct compare_pair_by_first {
    template<class T1, class T2> bool operator()(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right) {
        return P<T2>()(left.first, right.first);
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
template<template <typename> class P = std::less >
struct compare_pair_by_second {
    template<class T1, class T2> bool operator()(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right) {
        return P<T2>()(left.second, right.second);
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class T2, class Pred = std::less<T> >
#else
template<class T1, class T2, class Pred = std::less<class T> >
#endif
struct compare_vector_by_specified_column {
public:
	int n1, n2;
	bool operator()(const std::vector<T1> & left, const std::vector<T2> & right) {
        Pred p;
        return p(left[n1], right[n2]);
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
#ifdef WINDOWS
template<class T1, class T2>
#else
template<class T1, class T2>
#endif
class VectorComparator
{
private:
	std::vector<int> m_vectorSortColumns;
	bool m_bAscending;

public:
	explicit VectorComparator<T1, T2>(std::vector<int> sortColumns, bool bAscending = true)
		: m_vectorSortColumns(sortColumns),
		m_bAscending(bAscending)
    {
    }

	bool operator()(const std::vector<T1>& lhs, const std::vector<T2>& rhs) const
    {
        // For each sorting column:
        for (size_t i = 0; i < m_vectorSortColumns.size(); i++)
        {
            // Comparison with nCurrent column
            const int nCurrentColumnID = m_vectorSortColumns[i];

			if(lhs.size() < nCurrentColumnID+1 && rhs.size() < nCurrentColumnID+1){
				return m_bAscending ? false : true;
			}
			else if(lhs.size() < nCurrentColumnID+1 && rhs.size() >= nCurrentColumnID+1){
				return m_bAscending ? true : false;
			}
			else if(lhs.size() >= nCurrentColumnID+1 && rhs.size() < nCurrentColumnID+1){
				return m_bAscending ? false : true;
			}

            if (lhs[nCurrentColumnID] < rhs[nCurrentColumnID])
				return m_bAscending ? true : false;

            if (lhs[nCurrentColumnID] > rhs[nCurrentColumnID])
				return m_bAscending ? false : true;

            // lhs[nCurrentColumnID] == rhs[nCurrentColumnID],
            // so check with next sorting column
        }

		return m_bAscending ? false : true;
    }
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////



#endif//!__SORTHELPER_H__
