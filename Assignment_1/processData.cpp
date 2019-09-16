/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

string requestString, requestIN4;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}


Options resolveOptions(string& requestS, string& restS)
{
	if (requestS == "CL" && restS == "") return COUNT_LINE;
	if (requestS == "CL") return COUNT_LINE_of_CITY;
	if (requestS == "LSC") return LIST_STATION_of_CITY;
	if (requestS == "LLC") return LIST_LINE_of_CITY;
	if (requestS == "LSL") return LIST_STATION_of_LINE;
	if (requestS == "FC") return FIND_CITY;
	if (requestS == "FS") return FIND_STATION;
	if (requestS == "SLP") return FIND_STATION_of_TRACK;
	if (requestS == "IS") return INSERT_STATION;
	if (requestS == "RS") return REMOVE_STATION;
	if (requestS == "US") return UPDATE_STATION;
	if (requestS == "ISL") return INSERT_STATION_to_LINE;
	if (requestS == "RSL") return REMOVE_STATION_from_LINE;
}

//       pData is a pointer to a data structure that manages the dataset
   //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
   //       N is the size of output, must be a non-negative number
void ProcessRequest(const char* pRequest, void*& pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
	requestString = "";
	while (*pRequest != ' ' && *pRequest != '\0') 
		requestString += *(pRequest++);
	requestIN4 = ++pRequest;

	int* outputData = new int[50000];
	pOutput = outputData; N = 0;
	
    switch (resolveOptions(requestString, requestIN4))
    {
		case COUNT_LINE:
			countLine_1((TDataset*&)pData, outputData, N);
    		break;
		case COUNT_LINE_of_CITY:
			countLineofCity_2((TDataset * &)pData, outputData, N);
			break;
		case LIST_STATION_of_CITY:
			ListStationOfCity_3((TDataset * &)pData, outputData, N);
    		break;
		case LIST_LINE_of_CITY:
			ListLinesOfCity_4((TDataset * &)pData, outputData, N);
    		break;
		case LIST_STATION_of_LINE:
			ListStationOfLines_5((TDataset * &)pData, outputData, N);
    		break;
		case FIND_CITY:
			FindCityIdbyName_6((TDataset * &)pData, outputData, N);
			break;
		case FIND_STATION:
			FindStationIdbyName_7((TDataset * &)pData, outputData, N);
			break;
		case FIND_STATION_of_TRACK:
			FindStationinTrack_8((TDataset * &)pData, outputData, N);
			break;
		case INSERT_STATION:
			InsertStation_9((TDataset * &)pData, outputData, N);
			break;
		case REMOVE_STATION: break;
		case UPDATE_STATION: break;
		case INSERT_STATION_to_LINE: break;
		case REMOVE_STATION_from_LINE: break;
    }
}

// Solve
void countLine_1(TDataset*& pData, int*& outputData, int& N)
{
	N = 1;
	outputData[0] = pData->line->getSize();
}

int getCityIdByName(TDataset*& pData, string nameS)
{
	L1Item<TCity>* node = pData->city->get_p_head();
	while (node != nullptr && node->data.name != nameS)
		node = node->pNext;
	if (node == nullptr) return -1;
	return node->data.id;
}

void countLineofCity_2(TDataset*& pData, int*& outputData, int& N)
{
	N = 1;
	int cityId = getCityIdByName(pData, requestIN4);
	if (cityId == -1)
	{
		outputData[0] = -1;
		return;
	}
	//count by city ID
	int res = 0;
	L1Item<TLine>* node = pData->line->get_p_head();
	while (node != nullptr)
	{
		if (node->data.cityId == cityId)
			++res;
		node = node->pNext;
	}
	outputData[0] = res;
}

void ListStationOfCity_3(TDataset*& pData, int*& outputData, int& N)
{
	int cityId = getCityIdByName(pData, requestIN4);
	if (cityId == -1)
	{
		N = 1;
		outputData[0] = -1;
		return;
	}
	//find by city ID
	L1Item<TStation>* node = pData->station->get_p_head();
	while (node != nullptr)
	{
		if (node->data.cityId == cityId)
			outputData[++N - 1] = node->data.id;
		node = node->pNext;
	}
}

void ListLinesOfCity_4(TDataset*& pData, int*& outputData, int& N)
{
	int cityId = getCityIdByName(pData, requestIN4);
	if (cityId == -1)
	{
		N = 1;
		outputData[0] = -1;
		return;
	}
	//find by city ID
	L1Item<TLine>* node = pData->line->get_p_head();
	while (node != nullptr)
	{
		if (node->data.cityId == cityId)
			outputData[++N - 1] = node->data.id;
		node = node->pNext;
	}
}

void ListStationOfLines_5(TDataset*& pData, int*& outputData, int& N)
{
	L1Item<Station_Line>* node = pData->station_Line->get_p_head();
	int lineIdin4 = stoi(requestIN4);
	while (node != nullptr)
	{
		if (node->data.lineId == lineIdin4)
			outputData[++N - 1] = node->data.stationId;
		node = node->pNext;
	}
}

void FindCityIdbyName_6(TDataset*& pData, int*& outputData, int& N)
{
	N = 1;
	int cityId = getCityIdByName(pData, requestIN4);
	if (cityId == -1)
		outputData[0] = -1;
	else outputData[0] = cityId;
}

void FindStationIdbyName_7(TDataset*& pData, int*& outputData, int& N)
{
	N = 1;
	L1Item<TStation>* node = pData->station->get_p_head();
	while (node != nullptr && node->data.name != requestIN4)
		node = node->pNext;
	if (node == nullptr) outputData[0] = -1;
	else outputData[0] = node->data.id;
}

void FindStationinTrack_8(TDataset*& pData, int*& outputData, int& N)
{
	N = 1;
	int spacePosition = requestIN4.find_first_of(" ");
	int stationId = stoi(requestIN4.substr(0, spacePosition));
	requestIN4.erase(0, spacePosition + 1);
	int trackId = stoi(requestIN4);
	//get Station Coordinate
	string coordinate;
	L1Item<TStation>* nodeStation = pData->station->get_p_head();
	while (nodeStation != nullptr && nodeStation->data.id != stationId)
		nodeStation = nodeStation->pNext;
	coordinate = nodeStation->data.coordinate;
	//get pTrack
	L1Item<TTrack>* nodeTrack = pData->track->get_p_head();
	while (nodeTrack != nullptr && nodeTrack->data.id != trackId)
		nodeTrack = nodeTrack->pNext;
	//check if not found
	if (nodeStation == nullptr || nodeTrack == nullptr)
	{
		outputData[0] = -1;
		return;
	}
	//find position
	int position = 0;
	int found = (nodeTrack->data.lineString).find(coordinate);
	if (found == string::npos)
	{
		outputData[0] = -1;
		return;
	}
	while(--found > 0)
		if (nodeTrack->data.lineString[found] == ',') ++position;
	outputData[0] = position;
}

void InsertStation_9(TDataset*& pData, int*& outputData, int& N)
{
	string name, point;
	if (requestIN4[0] == '\"')
		name = frontToNextDoubleQuotes(requestIN4);
	else name = frontToNextComma(requestIN4);
	point = frontToNextComma(requestIN4);
	//POINT() = 7
	point = point.substr(6, point.length() - 7);

	int id, cityId;
	getMaxStation_CityId(pData, id, cityId);
	
	TStation temp(id, name, point, cityId);
	pData->station->push_back(temp);
}
//Support InsertStation_9
void getMaxStation_CityId(TDataset*& pData, int& mStation, int& mCity)
{
	L1Item<TStation>* node = pData->station->get_p_head();
	mStation = node->data.id; mCity = node->data.cityId;
	while (node != nullptr)
	{
		if (mStation < node->data.id) mStation = node->data.id;
		if (mCity < node->data.cityId) mCity = node->data.cityId;
		node = node->pNext;
	}
}
