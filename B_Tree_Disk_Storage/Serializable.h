#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

using namespace std;

class Serializable {
public:
	Serializable() {}
	virtual ~Serializable() {}
	virtual string ToString() = 0;
	virtual string ToCSV() = 0;
	virtual string ToXML() = 0;
	virtual string ToJSON() = 0;
	virtual void FromString(string repr) = 0;
	virtual void FromCSV(string repr) = 0;
	virtual void FromXML(string repr) = 0;
	virtual void FromJSON(string repr) = 0;


};

#endif
