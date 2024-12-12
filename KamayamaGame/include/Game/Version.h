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
		if (major > rHand.getMajor()) return false;//major‚ªã‰ñ‚é
		if (major < rHand.getMajor())return true;//major‚ª‰º‰ñ‚é
		//ˆÈ‰ºmajor=rHand.major
		if (minor > rHand.getMinor()) return false;//minor‚ªã‰ñ‚é
		if (minor < rHand.getMinor())return true;//minor‚ª‰º‰ñ‚é
		//ˆÈ‰ºminor=rHand.minor
		if (maintenance > rHand.getMaintenance()) return false;//maintenance‚ªã‰ñ‚é
		if (maintenance < rHand.getMaintenance())return true;//maintenance‚ª‰º‰ñ‚é
		//‘S‚Ä“™‚µ‚¢
		return false;
	}

	bool operator>(const Version& rHand) {
		return rHand < *this;
	}

	bool operator==(const Version& rHand)const {
		return major == rHand.getMajor() && minor == rHand.getMinor() && maintenance == rHand.getMaintenance();
	}

	//cerial—p
	template <class Archive>
	void serialize(Archive& archive) {
		archive(major, minor, maintenance);
	}
};