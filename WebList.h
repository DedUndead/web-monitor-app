#pragma once

#include <vector>
#include <string>
#include "WebPage.h"

/// <summary>
/// WebList class is used for handling page lists.
/// Default check time is 300 second.
/// </summary>
class WebList {
public:
	WebList(int time = 300) : webList(), checkTime(time) {}
	bool uploadList(const std::string& filename);
	void checkAll();
	void saveLog() const;
private:
	std::vector<WebPage> webList;
	int checkTime;
};
