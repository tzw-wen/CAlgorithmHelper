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

#include "KnapsackHelper.h"
#include <iomanip>

void KnapsackItem::Reset() {
	m_sName = _T("");
	m_dWeight = 0.0;
	m_dValue = 0.0;
	m_nBounding = 1;
	m_nInKnapsack = 0;
}

KnapsackItem::KnapsackItem() {
	Reset();
}
 
//KnapsackItem::KnapsackItem(const KnapsackItem & item) {
//	Reset();
//	//
//  setName(item.m_sName);
//  setWeight(item.m_dWeight);	
//  setValue(item.m_dValue);
//  setBounding(item.m_nBounding);
//	setInKnapsack(item.m_nInKnapsack);
//}
 
KnapsackItem::KnapsackItem(double dWeight, double dValue) {
	Reset();
	//
    setWeight(dWeight);
    setValue(dValue);
}

KnapsackItem::KnapsackItem(double dWeight, double dValue, int nBounding) {
	Reset();
	//
    setWeight(dWeight);
    setValue(dValue);
    setBounding(nBounding);
}

KnapsackItem::KnapsackItem(_tstring sName, double dWeight, double dValue) {
	Reset();
	//
    setName(sName);
    setWeight(dWeight);
    setValue(dValue);
}

KnapsackItem::KnapsackItem(_tstring sName, double dWeight, double dValue, int nBounding) {
	Reset();
	//
    setName(sName);
    setWeight(dWeight);
    setValue(dValue);
    setBounding(nBounding);
}

void KnapsackItem::setName(_tstring sName) {m_sName = sName;}
void KnapsackItem::setWeight(double dWeight) {m_dWeight = dWeight > 0 ? dWeight : 0;}
void KnapsackItem::setValue(double dValue) {m_dValue = dValue > 0 ? dValue : 0;}

void KnapsackItem::setInKnapsack(int nInKnapSack) {
	nInKnapSack = nInKnapSack > 0 ? nInKnapSack : 0;
	m_nInKnapsack = m_nBounding < nInKnapSack ? m_nBounding : nInKnapSack;
}

void KnapsackItem::setBounding(int nBounding) {
	nBounding = nBounding > 0 ? nBounding : 0;
	nBounding = nBounding > m_nInKnapsack ? nBounding : m_nInKnapsack;
	m_nBounding = nBounding;    
}

void KnapsackItem::checkMembers() {
    setWeight(m_dWeight);
    setValue(m_dValue);
    setBounding(m_nBounding);
    setInKnapsack(m_nInKnapsack);
}

_tstring KnapsackItem::getName() const {
	return m_sName;
}

double KnapsackItem::getWeight() const {
	return m_dWeight;
}

double KnapsackItem::getValue() const {
	return m_dValue;
}

int KnapsackItem::getInKnapsack() const {return m_nInKnapsack;
}

int KnapsackItem::getBounding() const {
	return m_nBounding;
}

bool KnapsackItem::Comparer(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2){
	return knapsackItem1 < knapsackItem2;
}

bool KnapsackItem::ComparerByGreaterValueRate(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2) {
    double rate1 = knapsackItem1.getValue() / knapsackItem1.getWeight();
    double rate2 = knapsackItem2.getValue() / knapsackItem2.getWeight();
    if (rate1 > rate2) 
		return true;  // if greater, put it previously
    else if (rate1 < rate2) 
		return false;
	else 
		return Comparer(knapsackItem1, knapsackItem2);
}

bool KnapsackItem::operator()(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2) const{
	return Comparer(knapsackItem1, knapsackItem2);
}

bool KnapsackItem::operator < (const KnapsackItem & knapsackItem) const{
	if(m_sName < knapsackItem.m_sName){
		return true;
	}
	else if(m_sName > knapsackItem.m_sName){
		return false;
	}
	else{
		if(m_dWeight < knapsackItem.m_dWeight){
			return true;
		}
		else if(m_dWeight > knapsackItem.m_dWeight){
			return false;
		}
		else{
			if(m_dValue < knapsackItem.m_dValue){
				return true;
			}
			else if(m_dValue > knapsackItem.m_dValue){
				return false;
			}
			else{
				if(m_nBounding < knapsackItem.m_nBounding){
					return true;
				}
				else if(m_nBounding > knapsackItem.m_nBounding){
					return false;
				}
				else{
					if(m_nInKnapsack < knapsackItem.m_nInKnapsack){
						return true;
					}
					else if(m_nInKnapsack > knapsackItem.m_nInKnapsack){
						return false;
					}
					else{
						return true;
					}
				}
			}
		}
	}
}

bool KnapsackItem::operator != (const KnapsackItem & knapsackItem) const{
	return 
		!(*this == knapsackItem);
}

bool KnapsackItem::operator == (const KnapsackItem & knapsackItem) const{
	return
		m_sName == knapsackItem.m_sName
		&&
		m_dWeight == knapsackItem.m_dWeight
		&&
		m_dValue == knapsackItem.m_dValue
		&&
		m_nBounding == knapsackItem.m_nBounding
		&&
		m_nInKnapsack == knapsackItem.m_nInKnapsack;
}


ZeroOneKnapsack::ZeroOneKnapsack() {
	Reset();
}

void ZeroOneKnapsack::Reset() {
	m_vectorItems.clear();
	m_dMaxWeight        = 0.0;
	m_dSolutionWeight   = 0.0;
	m_dProfit           = 0.0;
	m_bCalculated   = false;
}
 
 
ZeroOneKnapsack::ZeroOneKnapsack(int dMaxWeight) {
    setMaxWeight(dMaxWeight);
}
 
ZeroOneKnapsack::ZeroOneKnapsack(const std::vector<KnapsackItem> & vectorItems) {
    setVectorKnapsackItems(vectorItems);
}
 
ZeroOneKnapsack::ZeroOneKnapsack(const std::vector<KnapsackItem> & vectorItems, int dMaxWeight) {
    setVectorKnapsackItems(vectorItems);
    setMaxWeight(dMaxWeight);
}

//  inputs:
//    nn - number of items
//    v - vector of item values
//    w - vector of item weights
//    W - capacity of the knapsack
//    choice - pointer to a valid memory block in which to place the best found selection
//  output:
//    best found value of the knapsack
// calculte the solution of 0-1 knapsack problem with dynamic method:
double ZeroOneKnapsack::solve_knapsack(int nn, double *v, double *w, double W, int WEIGHT_BINS, std::vector<int> & choice)
{	
	choice.clear();
	//
	if(nn < 1){
		return 0.0;
	}
	//
	if(WEIGHT_BINS < 1){
		WEIGHT_BINS = 1;
	}
	//
	if(WEIGHT_BINS <= 1){
		std::vector<double> vectorW(nn);
		for(size_t i=0; i<nn; ++i){
			vectorW[i] = *(w+i);
		}
		std::sort(vectorW.begin(), vectorW.end(), std::greater<double>());
		double dMaxSingleW = vectorW[0];
		if(WEIGHT_BINS < std::floor(abs(dMaxSingleW)*10+0.5)){
			WEIGHT_BINS = std::floor(abs(dMaxSingleW)*10+0.5);
		}
		//
		double dMinSingleW = vectorW[vectorW.size()-1];
		//
		if(WEIGHT_BINS < std::floor(W/dMinSingleW+0.5)*2){
			WEIGHT_BINS = std::floor(W/dMinSingleW+0.5)*2;
		}
		//
		//int nDigits=1;
		//double dd = dMinSingleW;
		//while(fabs(dd*nDigits)<1){
		//	nDigits=nDigits*10;			
		//}
		//WEIGHT_BINS*=nDigits;
	}
	//
	//std::cout << "WEIGHT_BINS=" << WEIGHT_BINS << "\n";
	//
	double w_step = W / WEIGHT_BINS;
	//std::cout << "w_step=" << w_step << "\n";
	//init vectorVectorV and vectorVectorKeep
	std::vector<std::vector<double> > vectorVectorV;
	std::vector<std::vector<bool> > vectorVectorKeep;
	int nTotalRows = nn+1;
	int nTotalCols = WEIGHT_BINS+1;
	for(size_t i=0; i<nTotalRows; ++i){
		std::vector<double> vectorV(nTotalCols);
		std::vector<bool> vectorKeep(nTotalCols);
		for(size_t j=0; j<nTotalCols; ++j){
			vectorV[j] = 0.0;
			vectorKeep[j] = false;
		}
		vectorVectorV.push_back(vectorV);
		vectorVectorKeep.push_back(vectorKeep);
	}
	for(size_t i=1; i<nTotalRows; ++i){
		for(size_t j=0; j<nTotalCols; ++j){
			double dCurW = j*w_step;
			double n=std::floor((dCurW-(*(w+i-1)))/w_step);
			if(n < 0)
				n = 0;
			if(*(w+i-1)<=dCurW && (*(v+i-1)+vectorVectorV[i-1][n] > vectorVectorV[i-1][j])){
				vectorVectorV[i][j] = *(v+i-1)+vectorVectorV[i-1][n];
				vectorVectorKeep[i][j] = 1;
			}
			else{
				vectorVectorV[i][j] = vectorVectorV[i-1][j];
				vectorVectorKeep[i][j] = 0;
			}
		}
	}
	//
	int k=nTotalCols-1;
	for(size_t i=nTotalRows-1; i>=1; --i){
		if(vectorVectorKeep[i][k] == 1){
			choice.push_back(i-1);
			//std::cout << "i-1:" << i-1 << "\n";
			k=k-std::floor(*(w+i-1)/w_step+0.5);
			if(k < 0){
				break;
			}
		}
	}
	
	//
	return vectorVectorV[nTotalRows-1][nTotalCols-1];
}


// add an item to the item list
void ZeroOneKnapsack::add(_tstring name, double weight, double value) {
	if (name.length() < 1){
		std::stringstream ss;
		ss << (m_vectorItems.size() + 1);
        name = ss.str();
	}
	//for(size_t i=0; i<m_vectorItems.size(); ++i){
	//	if(m_vectorItems[i].getName() == name){
	//		if(m_vectorItems[i].getWeight() != weight ||
	//			m_vectorItems[i].getValue() != value){
	//			//error
	//		}
	//		//
	//		return;
	//	}
	//}
	//
	KnapsackItem item(name, weight, value);
    m_vectorItems.push_back(item);
    setInitialStateForCalculation();
}

// add an item to the item list
void ZeroOneKnapsack::add(double weight, double value) {
    add(_T(""), weight, value); // the name will be "vectorItems.size() + 1"!
}

// remove an item from the item list
void ZeroOneKnapsack::remove(_tstring name, std::vector<size_t> &vectorRemovedItemIDs) {
	vectorRemovedItemIDs.clear();
	//
	std::vector<KnapsackItem> vectorItems;
	for(size_t i=0; i<m_vectorItems.size(); ++i){
		if(m_vectorItems[i].getName() == name){
			vectorRemovedItemIDs.push_back(i);
		}
		else{
			vectorItems.push_back(m_vectorItems[i]);
		}
	}
    m_vectorItems = vectorItems;
    setInitialStateForCalculation();
}

// remove all items from the item list
void ZeroOneKnapsack::removeAllKnapsackItems() {
    m_vectorItems.clear();
    setInitialStateForCalculation();
}

double ZeroOneKnapsack::getProfit() {
    if (!m_bCalculated)
        calcSolution(0.01);
    return m_dProfit;
}

double ZeroOneKnapsack::getSolutionWeight() const {return m_dSolutionWeight;}

bool ZeroOneKnapsack::isCalculated() const {return m_bCalculated;}

double ZeroOneKnapsack::getMaxWeight() const {return m_dMaxWeight;}

void ZeroOneKnapsack::setMaxWeight(double dMaxWeight) {
	m_dMaxWeight = dMaxWeight > 0 ? dMaxWeight : 0;
	//
	setBoundingByAll(1);
    setInKnapsackByAll(0);
	//
	setInitialStateForCalculation();
}

void ZeroOneKnapsack::setVectorKnapsackItems(const std::vector<KnapsackItem> & vectorItems) {
    m_vectorItems.clear();
	m_vectorItems = vectorItems;
	for(size_t i=0; i<m_vectorItems.size(); ++i){
		m_vectorItems[i].checkMembers();
	}
	//
	setBoundingByAll(1);
    setInKnapsackByAll(0);
	//
	setInitialStateForCalculation();
}

// set the member with name "Bounding" by all items:
void ZeroOneKnapsack::setBoundingByAll(int bounding){
	for(size_t i=0; i<m_vectorItems.size(); ++i){
		m_vectorItems[i].setBounding(bounding >=  m_vectorItems[i].getInKnapsack() ? bounding :  m_vectorItems[i].getInKnapsack());
	}
	//
	setInitialStateForCalculation();
}

// set the member with name "inKnapsack" by all items:
void ZeroOneKnapsack::setInKnapsackByAll(int inKnapsack) {
    for(size_t i=0; i<m_vectorItems.size(); ++i){
        if (inKnapsack > 0)
            m_vectorItems[i].setInKnapsack(inKnapsack);
        else
            m_vectorItems[i].setInKnapsack(0);
	}
}


// set the data members of class in the state of starting the calculation:
void ZeroOneKnapsack::setInitialStateForCalculation() {		
    m_bCalculated     = false;
    m_dProfit         = 0;
    m_dSolutionWeight = 0;
	m_vectorItemsSelected.clear();
}

std::vector<KnapsackItem> ZeroOneKnapsack::getVectorItems() const {
	return  m_vectorItems;
}

std::vector<KnapsackItem> ZeroOneKnapsack::getVectorItemsSelected() const {
	return  m_vectorItemsSelected;
}

// calculte the solution of 0-1 knapsack problem with dynamic method:
void ZeroOneKnapsack::calcSolution() {
	calcSolution(0);
}

// calculte the solution of 0-1 knapsack problem with dynamic method:
void ZeroOneKnapsack::calcSolution(int WEIGHT_BINS) {
	setBoundingByAll(1);
    setInKnapsackByAll(0);
	//
	setInitialStateForCalculation();
	//
	if(m_vectorItems.size() < 1){
		return;
	}
	//
	std::vector<int> choice;
	std::vector<double> v(m_vectorItems.size());
	std::vector<double> w(m_vectorItems.size());
	size_t nn=m_vectorItems.size();
	for(size_t i=0; i<nn; ++i){
		v[i] = m_vectorItems[i].getValue();
		w[i] = m_vectorItems[i].getWeight();
		//std::cout << std::fixed << std::setprecision(5) << i << ":v=" << v[i] << ",w=" << w[i] << "\n";
	}
	//
	double dVal = solve_knapsack(nn, &v[0], &w[0], m_dMaxWeight, WEIGHT_BINS, choice);
	//std::cout << "dVal=" << dVal << "\n";
	//
	m_dSolutionWeight=0.0;
	m_dProfit = 0.0;
	for(size_t i=0; i<choice.size(); ++i){
		if(choice[i] < 0){
			continue;
		}
		m_vectorItems[choice[i]].setInKnapsack(1);
		m_dSolutionWeight += m_vectorItems[choice[i]].getWeight();
		m_dProfit += m_vectorItems[choice[i]].getValue();
		//
		KnapsackItem selectedItem = m_vectorItems[choice[i]];
		m_vectorItemsSelected.push_back(selectedItem);			
	}
	//
	m_bCalculated = true;
}

BoundingKnapsack::BoundingKnapsack(){
	Reset();
}

BoundingKnapsack::BoundingKnapsack(int dMaxWeight){
	Reset();
	setMaxWeight(dMaxWeight);
}

void BoundingKnapsack::Reset(){
	m_zeroOneKnapsack.Reset();
	m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack.clear();
}

// add an item to the item list
void BoundingKnapsack::add(_tstring name, double weight, double value, size_t nBounding){
	std::vector<size_t> vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	std::map<size_t, std::set<size_t> > mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	getMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack(
		vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack,
		mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack);
	size_t nItemIDInBoundingKnapsack = mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.size();
	size_t nItemIDInZeroOneKnapsack = m_zeroOneKnapsack.getVectorItems().size();
	for(size_t i=0; i<nBounding; ++i){
		m_zeroOneKnapsack.add(name, weight, value);
		//
		m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack[nItemIDInZeroOneKnapsack+i] 
			= nItemIDInBoundingKnapsack;
	}
}

// add an item to the item list
void BoundingKnapsack::add(double weight, double value, size_t nBounding){
	_tstring name;
	//
	std::vector<KnapsackItem> vectorItems = getVectorItems();
	std::stringstream ss;
	ss << (vectorItems.size() + 1);
    name = ss.str();
	//
	add(name, weight, value, nBounding);
}

// remove an item from the item list
void BoundingKnapsack::remove(_tstring name, std::vector<size_t> &vectorRemovedItemIDs){
	m_zeroOneKnapsack.remove(name, vectorRemovedItemIDs);
	//
	for(size_t i=0; i<vectorRemovedItemIDs.size(); ++i){
		m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack.erase(vectorRemovedItemIDs[i]);
	}
}

// remove all items from the item list
void BoundingKnapsack::removeAllKnapsackItems(){
	m_zeroOneKnapsack.removeAllKnapsackItems();
	m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack.clear();
}

double BoundingKnapsack::getProfit(){
	return m_zeroOneKnapsack.getProfit();
}

void BoundingKnapsack::getMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack(
	std::vector<size_t> & vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack,
	std::map<size_t, std::set<size_t> > & mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack) const{		
	std::map<size_t, size_t>::const_iterator citMapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack
		= m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack.begin();
	for(; citMapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack
		!= m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack.end();
		++citMapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack){
		size_t nItemIDInZeroOneKnapsack = citMapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack->first;
		size_t nItemIDInBoundingKnapsack = citMapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack->second;
		std::map<size_t, std::set<size_t> >::iterator itMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack
			= mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.find(nItemIDInBoundingKnapsack);
		if(itMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack
			== mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.end()){
			std::set<size_t> setItemIDsInZeroOneKnapsack;
			setItemIDsInZeroOneKnapsack.insert(nItemIDInZeroOneKnapsack);
			mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack[nItemIDInBoundingKnapsack]
			= setItemIDsInZeroOneKnapsack;
			//
			vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.push_back(nItemIDInBoundingKnapsack);
		}
		else{
			itMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack->second.insert(nItemIDInZeroOneKnapsack);
		}
	}
	//
	std::sort(vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.begin(), vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.end(), std::less<size_t>());
}

std::vector<KnapsackItem> BoundingKnapsack::getVectorItems() const{	
	std::map<size_t, std::set<size_t> > mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	std::vector<size_t> vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	getMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack(
		vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack,
		mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack);
	//
	std::vector<KnapsackItem> vectorItems = m_zeroOneKnapsack.getVectorItems();
	//
	std::vector<KnapsackItem> vectorRS;
	//
	for(size_t i=0; i<vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.size(); ++i){
		size_t nItemIDInBoundingKnapsack = vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack[i];
		std::set<size_t> setItemIDsInZeroOneKnapsack = mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack[nItemIDInBoundingKnapsack];
		std::set<size_t>::iterator itSetItemIDsInZeroOneKnapsack = setItemIDsInZeroOneKnapsack.begin();
		size_t n=0;
		for(; itSetItemIDsInZeroOneKnapsack != setItemIDsInZeroOneKnapsack.end();
			++itSetItemIDsInZeroOneKnapsack){
			n += vectorItems[*itSetItemIDsInZeroOneKnapsack].getInKnapsack();
		}
		KnapsackItem knapsackItem = vectorItems[*(setItemIDsInZeroOneKnapsack.begin())];
		//
		knapsackItem.setBounding(setItemIDsInZeroOneKnapsack.size());
		//
		knapsackItem.setInKnapsack(n);
		//
		vectorRS.push_back(knapsackItem);
	}
	//
	return vectorRS;
}

std::vector<KnapsackItem> BoundingKnapsack::getVectorItemsSelected() const{
	std::map<size_t, std::set<size_t> > mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	std::vector<size_t> vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack;
	getMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack(
		vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack,
		mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack);
	//
	std::vector<KnapsackItem> vectorItems = m_zeroOneKnapsack.getVectorItems();
	//
	std::vector<KnapsackItem> vectorRS;
	//
	for(size_t i=0; i<vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack.size(); ++i){
		size_t nItemIDInBoundingKnapsack = vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack[i];
		std::set<size_t> setItemIDsInZeroOneKnapsack = mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack[nItemIDInBoundingKnapsack];
		std::set<size_t>::iterator itSetItemIDsInZeroOneKnapsack = setItemIDsInZeroOneKnapsack.begin();
		size_t n=0;
		for(; itSetItemIDsInZeroOneKnapsack != setItemIDsInZeroOneKnapsack.end();
			++itSetItemIDsInZeroOneKnapsack){
			n += vectorItems[*itSetItemIDsInZeroOneKnapsack].getInKnapsack();
		}
		//
		if(n > 0){
			KnapsackItem knapsackItem = vectorItems[*(setItemIDsInZeroOneKnapsack.begin())];
			//
			knapsackItem.setBounding(setItemIDsInZeroOneKnapsack.size());
			//
			knapsackItem.setInKnapsack(n);
			//
			vectorRS.push_back(knapsackItem);
		}
	}
	//
	return vectorRS;
}

double BoundingKnapsack::getSolutionWeight() const{
	return m_zeroOneKnapsack.getSolutionWeight();
}

bool BoundingKnapsack::isCalculated() const{
	return m_zeroOneKnapsack.isCalculated();
}

double BoundingKnapsack::getMaxWeight() const{
	return m_zeroOneKnapsack.getMaxWeight();
}

void BoundingKnapsack::setMaxWeight(double dMaxWeight){
	m_zeroOneKnapsack.setMaxWeight(dMaxWeight);
}

// set the member with name "Bounding" by all items:
void BoundingKnapsack::setBoundingByAll(int bounding){
	m_zeroOneKnapsack.setBoundingByAll(bounding);
}

// calculte the solution of 0-1 knapsack problem with dynamic method:
void BoundingKnapsack::calcSolution(int WEIGHT_BINS){
	m_zeroOneKnapsack.calcSolution(WEIGHT_BINS);
}

// calculte the solution of 0-1 knapsack problem with dynamic method:
void BoundingKnapsack::calcSolution(){
	m_zeroOneKnapsack.calcSolution();
}