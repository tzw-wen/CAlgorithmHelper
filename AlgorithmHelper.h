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


#ifndef __ALGORITHMHELPER_H__
#define __ALGORITHMHELPER_H__

#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "StringHelper.h"

#include <iomanip>

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
class CCombinationIntTypeHelper {
public:
	CCombinationIntTypeHelper();
	~CCombinationIntTypeHelper();
	//
public:
	static void CombinationWithoutRepetitionForIntType(std::vector<int> & vectorCurrentCombination, int nStart, int nEnd, int nCurrentChosenElements, int nMaxChosenElements, std::vector<std::vector<int> > & vectorAllCombinationResults);

public:
	static void CombinationAllWithoutRepetitionForIntType(
		int nStart,
		int nEnd,
		std::vector<std::vector<int> > & vectorAllCombinationResults);

	static void CombinationAllWithoutRepetitionForIntType(
		int nStart,
		int nEnd,
		int nMaxChosenElementsMax,
		std::vector<std::vector<int> > & vectorAllCombinationResults);
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

#include "SortHelper.h"
#include "CombinationHelper.h"
#include "KnapsackHelper.h"





#endif//!__ALGORITHMHELPER_H__
