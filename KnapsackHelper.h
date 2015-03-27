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

#ifndef __KNAPSACKHELPER_H__
#define __KNAPSACKHELPER_H__

#pragma once

#include "StringHelper.h"

///////////////////////////////////////////////////////
#include "ALGORITHMHELPER_Export.h"
class KnapsackItem {
private:
    _tstring m_sName;
    double m_dWeight;
    double m_dValue;
    int m_nBounding; // the maximal limit of item's pieces
    int m_nInKnapsack; // the pieces of item in solution

public:
	KnapsackItem();

    //KnapsackItem(const KnapsackItem & item);

    KnapsackItem(double dWeight, double dValue);

    KnapsackItem(double dWeight, double dValue, int nBounding);

    KnapsackItem(_tstring sName, double dWeight, double dValue);

    KnapsackItem(_tstring sName, double dWeight, double dValue, int nBounding);

public:
	void Reset();

	static bool Comparer(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2);
	static bool ComparerByGreaterValueRate(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2);
public:
	bool operator()(const KnapsackItem & knapsackItem1, const KnapsackItem & knapsackItem2) const;
	bool operator < (const KnapsackItem & knapsackItem) const;
	bool operator != (const KnapsackItem & knapsackItem) const;
	bool operator == (const KnapsackItem & knapsackItem) const;

public:
	void setName(_tstring sName);
	void setWeight(double dWeight);
	void setValue(double dValue);

    void setInKnapsack(int nInKnapSack);

    void setBounding(int nBounding);

    void checkMembers();

    _tstring getName() const;
    double getWeight() const;
    double getValue() const;
    int getInKnapsack() const;
    int getBounding() const;

};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

#include "ALGORITHMHELPER_Export.h"
///////////////////////////////////////////////////////
class ZeroOneKnapsack {
private:
	std::vector<KnapsackItem> m_vectorItems;
	std::vector<KnapsackItem> m_vectorItemsSelected;
    double m_dMaxWeight;
    double m_dSolutionWeight;
    double m_dProfit;
    bool m_bCalculated;

public:
	ZeroOneKnapsack();

    ZeroOneKnapsack(int dMaxWeight);

	ZeroOneKnapsack(const std::vector<KnapsackItem> & vectorItems);

    ZeroOneKnapsack(const std::vector<KnapsackItem> & vectorItems, int dMaxWeight);

private:
	static double solve_knapsack(int nn, double *v, double *w, double W, int WEIGHT_BINS, std::vector<int> & choice);

public:
	void Reset();

    // add an item to the item list
    void add(_tstring name, double weight, double value);

    // add an item to the item list
    void add(double weight, double value);

    // remove an item from the item list
	void remove(_tstring name, std::vector<size_t> &vectorRemovedItemIDs);

    // remove all items from the item list
	void removeAllKnapsackItems();

	double getProfit();

	std::vector<KnapsackItem> getVectorItems() const;
	std::vector<KnapsackItem> getVectorItemsSelected() const;

    double getSolutionWeight() const;
    bool isCalculated() const;
    double getMaxWeight() const;

    void setMaxWeight(double dMaxWeight);

	void setVectorKnapsackItems(const std::vector<KnapsackItem> & vectorItems);

    // set the member with name "inKnapsack" by all items:
    void setInKnapsackByAll(int inKnapsack);

	// set the member with name "Bounding" by all items:
    void setBoundingByAll(int bounding);


    // set the data members of class in the state of starting the calculation:
    void setInitialStateForCalculation();

	// calculte the solution of 0-1 knapsack problem with dynamic method:
	void calcSolution(int WEIGHT_BINS);

	// calculte the solution of 0-1 knapsack problem with dynamic method:
	void calcSolution();
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

#include "ALGORITHMHELPER_Export.h"
///////////////////////////////////////////////////////
class BoundingKnapsack {
private:
	ZeroOneKnapsack m_zeroOneKnapsack;
	std::map<size_t, size_t> m_mapItemIDInZeroOneKnapsack_ItemIDInBoundingKnapsack;

public:
	BoundingKnapsack();
	BoundingKnapsack(int dMaxWeight);

public:
	void Reset();

    // add an item to the item list
    void add(_tstring name, double weight, double value, size_t nBounding);

    // add an item to the item list
    void add(double weight, double value, size_t nBounding);

    // remove an item from the item list
    void remove(_tstring name, std::vector<size_t> &vectorRemovedItemIDs);

    // remove all items from the item list
	void removeAllKnapsackItems();

	double getProfit();

	void getMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack(
		std::vector<size_t> & vectorKeysOfMapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack,
		std::map<size_t, std::set<size_t> > & mapItemIDInBoundingKnapsack_SetItemIDsInZeroOneKnapsack) const;
	std::vector<KnapsackItem> getVectorItems() const;
	std::vector<KnapsackItem> getVectorItemsSelected() const;

    double getSolutionWeight() const;
    bool isCalculated() const;
    double getMaxWeight() const;

    void setMaxWeight(double dMaxWeight);

	// set the member with name "Bounding" by all items:
    void setBoundingByAll(int bounding);

	// calculte the solution of 0-1 knapsack problem with dynamic method:
	void calcSolution(int WEIGHT_BINS);

	// calculte the solution of 0-1 knapsack problem with dynamic method:
	void calcSolution();
};
#include "ALGORITHMHELPER_Deport.h"
///////////////////////////////////////////////////////

#endif//!__KNAPSACKHELPER_H__

