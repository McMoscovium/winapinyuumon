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
		if (major > rHand.getMajor()) return false;//majorが上回る
		if (major < rHand.getMajor())return true;//majorが下回る
		//以下major=rHand.major
		if (minor > rHand.getMinor()) return false;//minorが上回る
		if (minor < rHand.getMinor())return true;//minorが下回る
		//以下minor=rHand.minor
		if (maintenance > rHand.getMaintenance()) return false;//maintenanceが上回る
		if (maintenance < rHand.getMaintenance())return true;//maintenanceが下回る
		//全て等しい
		return false;
	}

	bool operator>(const Version& rHand) {
		return rHand < *this;
	}

	bool operator==(const Version& rHand)const {
		return major == rHand.getMajor() && minor == rHand.getMinor() && maintenance == rHand.getMaintenance();
	}

	//cerial用
	template <class Archive>
	void serialize(Archive& archive) {
		archive(major, minor, maintenance);
	}
};