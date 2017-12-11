#include "design.h"

//const QString Colors::explorer = "#252526";
//const QString Colors::explorer = "#007acc";
//const QString Colors::explorer = "#2d2d30";
//const QString Colors::explorer = "#171718";

Design* Design::m_instance = nullptr;

Design::Design() {

	float dpi = qApp->primaryScreen()->physicalDotsPerInch();
//#ifdef  Q_OS_WIN
//	scaleFactor = dpi / 96.0;
//#elif Q_OS_ANDROID
//	scaleFactor = dpi / 160.0;
//#elif Q_OS_IOS			
//#endif // !Q_OS_

}

void Design::initialize() {
	m_menubarWidth = m_windowWidth;
	m_menubarHeight = pt(50);

	m_statusbarWidth = m_windowWidth;
	m_statusbarHeight = pt(30);

	m_borderFixedSize = pt(8);

	m_explorerWidth = pt(250);// m_windowWidth / 3;
	m_explorerHeight = m_windowHeight - m_menubarHeight - m_statusbarHeight;

	m_logWidth = m_previewWidth;
	m_logHeight = pt(200);//m_explorerHeight - m_previewHeight;

	m_previewWidth = m_windowWidth - m_explorerWidth - m_borderFixedSize;
	m_previewHeight = /*m_explorerHeight * 2 / 3*/ m_explorerHeight - m_logHeight - m_borderFixedSize;
}
