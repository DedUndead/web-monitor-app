#pragma once

#include <vector>
#include <string>
#include "WebPage.h"

/// <summary>
/// WebList class is used for handling page lists.
/// </summary>
class WebList {
public:
	WebList(int time = 300) : webList() {}
	bool uploadList(const std::string& filename);
	void checkAll();
	void saveLog() const;
	void updateHTML() const;
private:
	std::vector<WebPage> webList;
	std::string getTime() const;
	std::string getHeadHTML() const;
	std::string getTailHTML() const;
};
