/*
 * storage.h
 *
 *  Created on: Sep 30, 2022
 *      Author: KZ
 */

#ifndef STORAGE_H_
#define STORAGE_H_


#include "storage_base.h"
#include "KnowledgeItem.h"

#include <string>

//TODO: do we need a single storage class, or separate classes for save and load?
// single class means we should initialize fields with meaningless values
//template<typename OutStreamT, typename InStreamT, typename ResultT = std::string>
//class StreamStorage {
//public:
//	StreamStorage() {};
//	StreamStorage(const ResultT& data):outstream{}, instream{data} {}
//	void save(KnowledgeItemPtr item);
//	KnowledgeItemPtr load();
//private:
//	OutStreamT outstream;
//	InStreamT instream;
//};

template<typename OutStreamT, typename ResultT = std::string>
class StreamStorageSaver: public BaseStorageSaver {
public:
	StreamStorageSaver() {};
	void save(KnowledgeItemPtr item) override;

	void save_title(const std::string &title) override;
	void save_creation_time(Timestamp time) override;

	OutStreamT& underlying_stream() {return outstream;}

private:
	OutStreamT outstream;

};

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save(
		KnowledgeItemPtr item) {
	item->save_to(*this);
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_title(
		const std::string &title) {
	outstream<<title<<std::endl;
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_creation_time(Timestamp time) {
	outstream<<time_to_string(time)<<std::endl;
}

#endif /* STORAGE_H_ */