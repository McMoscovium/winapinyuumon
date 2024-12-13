#pragma once

#include <string>

class Version {
private:
	unsigned int major;
	unsigned int minor;
	unsigned int maintenance;
public:
	Version(
		unsigned int major,
		unsigned int minor,
		unsigned int maintenance
		):
		major(major),
		minor(minor),
		maintenance(maintenance){ }
	Version(const Version& version):
		major(version.getMajor()),
		minor(version.getMinor()),
		maintenance(version.getMaintenance())
	{

	}

	unsigned int getMajor()const { return major; }
	unsigned int getMinor()const { return minor; }
	unsigned int getMaintenance()const { return maintenance; }

	bool operator<(const Version& rHand)const {
		if (major > rHand.getMajor()) return false;//major������
		if (major < rHand.getMajor())return true;//major�������
		//�ȉ�major=rHand.major
		if (minor > rHand.getMinor()) return false;//minor������
		if (minor < rHand.getMinor())return true;//minor�������
		//�ȉ�minor=rHand.minor
		if (maintenance > rHand.getMaintenance()) return false;//maintenance������
		if (maintenance < rHand.getMaintenance())return true;//maintenance�������
		//�S�ē�����
		return false;
	}

	bool operator>(const Version& rHand) {
		return rHand < *this;
	}

	bool operator==(const Version& rHand)const {
		return major == rHand.getMajor() && minor == rHand.getMinor() && maintenance == rHand.getMaintenance();
	}

	//cerial�p
	template <class Archive>
	void serialize(Archive& archive) {
		archive(major, minor, maintenance);
	}
};