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


#include "AlgorithmHelper.h"

CCombinationIntTypeHelper::CCombinationIntTypeHelper(){
}

CCombinationIntTypeHelper::~CCombinationIntTypeHelper(){
}

void CCombinationIntTypeHelper::CombinationWithoutRepetitionForIntType(
	std::vector<int> & vectorCurrentCombination, 
	int nStart, 
	int nEnd, 
	int nCurrentChosenElements, 
	int nMaxChosenElements,
	std::vector<std::vector<int> > & vectorAllCombinationResults){
	//
	//
	if(nMaxChosenElements < 1){
		return;
	}
	//
	if(vectorCurrentCombination.size() != nMaxChosenElements + 1){
		vectorCurrentCombination.resize(nMaxChosenElements + 1);
	}
	//
    if(nCurrentChosenElements > nMaxChosenElements) {		
		//ignoring the first element of vectorCurrentCombination
		//and insert into vectorAllCombinationResults
		std::vector<int> vectorCurrentCombinationFinal;
		vectorAllCombinationResults.push_back(vectorCurrentCombinationFinal);
		for(size_t i=1; i<vectorCurrentCombination.size(); ++i){
			vectorAllCombinationResults[vectorAllCombinationResults.size()-1].push_back(
				vectorCurrentCombination[i]);
		}
        //
		return;
    }

    //
    for (int i=nStart; i<=nEnd; i++) {
        vectorCurrentCombination[nCurrentChosenElements] = i;

        //
        CCombinationIntTypeHelper::CombinationWithoutRepetitionForIntType (
			vectorCurrentCombination, 
			i+1, 
			nEnd, 
			nCurrentChosenElements+1, 
			nMaxChosenElements,
			vectorAllCombinationResults);
    }
}

void CCombinationIntTypeHelper::CombinationAllWithoutRepetitionForIntType(
	int nStart, 
	int nEnd, std::vector<std::vector<int> > & vectorAllCombinationResults){	
	//
	if(nEnd < nStart){
		return;
	}
	//
	for(int nMaxChosenElements = 1; nMaxChosenElements <=nEnd - nStart + 1; ++nMaxChosenElements){
		std::vector<int> vectorCurrentCombination;
		int nCurrentChosenElements = 1;
		CCombinationIntTypeHelper::CombinationWithoutRepetitionForIntType (
			vectorCurrentCombination, 
			nStart, 
			nEnd, 
			nCurrentChosenElements, 
			nMaxChosenElements,
			vectorAllCombinationResults);
	}
}

void CCombinationIntTypeHelper::CombinationAllWithoutRepetitionForIntType(
	int nStart, 
	int nEnd, int nMaxChosenElementsMax, std::vector<std::vector<int> > & vectorAllCombinationResults){	
	//
	if(nEnd < nStart){
		return;
	}
	//
	for(int nMaxChosenElements = 1; 
		nMaxChosenElements <=nEnd - nStart + 1 && nMaxChosenElements <= nMaxChosenElementsMax; 
		++nMaxChosenElements){
		std::vector<int> vectorCurrentCombination;
		int nCurrentChosenElements = 1;
		CCombinationIntTypeHelper::CombinationWithoutRepetitionForIntType (
			vectorCurrentCombination, 
			nStart, 
			nEnd, 
			nCurrentChosenElements, 
			nMaxChosenElements,
			vectorAllCombinationResults);
	}
}

