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

#ifndef __COMBINATIONHELPER_H__
#define __COMBINATIONHELPER_H__

#pragma once

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
template <class T>
class CCombinationAnyTypeHelper {
public:
	static void CombinationAllWithoutRepetitionForIntType(
		const std::vector<T> & vectorRawData,
		std::vector<std::vector<T> > & vectorAllCombinationResults){
		//combine with position
		std::vector<std::vector<int> > vectorAllCombinationPositionResults;
		int nStart = 0;
		int nEnd = vectorRawData.size() -1;
		CCombinationIntTypeHelper::CombinationAllWithoutRepetitionForIntType(
			nStart,
			nEnd,
			vectorAllCombinationPositionResults);
		//translate position into object
		for(size_t i=0; i<vectorAllCombinationPositionResults.size(); ++i){
			std::vector<T> vectorCurrentCombination;
			vectorAllCombinationResults.push_back(vectorCurrentCombination);
			//
			for(size_t j=0;
				j<vectorAllCombinationPositionResults[i].size();
				++j){
				vectorAllCombinationResults[vectorAllCombinationResults.size()-1].push_back(vectorRawData[vectorAllCombinationPositionResults[i][j]]);
			}
		}
	}

	static void CombinationAllWithoutRepetitionForIntType(
		int nMaxChosenElementsMax,
		const std::vector<T> & vectorRawData,
		std::vector<std::vector<T> > & vectorAllCombinationResults){
		//combine with position
		std::vector<std::vector<int> > vectorAllCombinationPositionResults;
		int nStart = 0;
		int nEnd = vectorRawData.size() -1;
		CCombinationIntTypeHelper::CombinationAllWithoutRepetitionForIntType(
			nStart,
			nEnd,
			nMaxChosenElementsMax,
			vectorAllCombinationPositionResults);
		//translate position into object
		for(size_t i=0; i<vectorAllCombinationPositionResults.size(); ++i){
			std::vector<T> vectorCurrentCombination;
			vectorAllCombinationResults.push_back(vectorCurrentCombination);
			//
			for(size_t j=0;
				j<vectorAllCombinationPositionResults[i].size();
				++j){
				vectorAllCombinationResults[vectorAllCombinationResults.size()-1].push_back(vectorRawData[vectorAllCombinationPositionResults[i][j]]);
			}
		}
	}

	static void CombinationAllWithoutRepetitionForIntType(
		const T * const pRawData,
		long nRawData,
		std::vector<std::vector<T> > & vectorAllCombinationResults){
		//combine with position
		std::vector<std::vector<int> > vectorAllCombinationPositionResults;
		int nStart = 0;
		int nEnd = nRawData -1;
		CCombinationIntTypeHelper::CombinationAllWithoutRepetitionForIntType(
			nStart,
			nEnd,
			vectorAllCombinationPositionResults);
		//translate position into object
		for(size_t i=0; i<vectorAllCombinationPositionResults.size(); ++i){
			std::vector<T> vectorCurrentCombination;
			vectorAllCombinationResults.push_back(vectorCurrentCombination);
			//
			for(size_t j=0;
				j<vectorAllCombinationPositionResults[i].size();
				++j){
				vectorAllCombinationResults[vectorAllCombinationResults.size()-1].push_back(pRawData[vectorAllCombinationPositionResults[i][j]]);
			}
		}
	}
};
#include "ALGORITHMHELPER_Deport.h"

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
template <class BidirectionalIterator>
class CPermutation{
public:
	//similar to std::next_permutation
	static bool Permutation(BidirectionalIterator first,
		BidirectionalIterator last) {
		if (first == last)
			return false;
		BidirectionalIterator i = first;
		++i;
		if (i == last)
			return false;
		i = last;
		--i;
		for(;;) {
			BidirectionalIterator ii = i--;
			if (*i <*ii) {
				BidirectionalIterator j = last;
				while (!(*i <*--j));
				std::iter_swap(i, j);
				std::reverse(ii, last);
				return true;
			}
			if (i == first) {
				std::reverse(first, last);
				return false;
			}
		}
	}
	
	static bool Combination(const BidirectionalIterator first, BidirectionalIterator k, const BidirectionalIterator last)
	{
		if ((first == last) || (first == k) || (last == k))
			return false;
		BidirectionalIterator itr1 = first;
		BidirectionalIterator itr2 = last;
		++itr1;
		if (last == itr1)
			return false;
		itr1 = last;
		--itr1;
		 itr1 = k;
		--itr2;
		while (first != itr1)
		{
			if (*--itr1 < *itr2)
			{
				BidirectionalIterator j = k;
				while (!(*itr1 < *j)) ++j;
				std::iter_swap(itr1,j);
				++itr1;
				++j;
				itr2 = k;
				std::rotate(itr1,j,last);
				while (last != j)
				{
				++j;
				++itr2;
				}
				std::rotate(k,itr2,last);
				return true;
			}
		 }
		std::rotate(first,k,last);
		return false;
	}
	//
};

#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
#endif//!__COMBINATIONHELPER_H__

