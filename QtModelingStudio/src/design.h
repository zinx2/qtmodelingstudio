#pragma once
#include <QObject>
#include <QScreen>
#include <QDebug>
#include <QGuiApplication>
#include <QMap>

/* Main Window Size */
//#define MIM_WINDOW_WIDTH  pt(960)
//#define MIM_WINDOW_HEIGHT pt(720)
//#define MAX_WINDOW_WIDTH  pt(1920)
//#define MAX_WINDOW_HEIGHT pt(1080)

class Colors {
public:
	const QString explorer = "#252526";
	const QString selected = "#007acc";
	const QString adjustbar = "#2d2d30";
	const QString black02 = "#171718";
	const QString background = "#2d2d30";
	const QString selectedGray = "#3f3f46";
	const QString preview = "#1e1e1e";
	const QString orange = "#f39c11";
};

class Design : public QObject {
	Q_OBJECT
		Q_PROPERTY(int windowWidth  READ windowWidth  WRITE setWindowWidth  NOTIFY windowWidthChanged)
		Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
		Q_PROPERTY(int menubarWidth  READ menubarWidth  WRITE setMenubarWidth  NOTIFY menubarWidthChanged)
		Q_PROPERTY(int menubarHeight READ menubarHeight WRITE setMenubarHeight NOTIFY menubarHeightChanged)
		Q_PROPERTY(int toolbarWidth  READ toolbarWidth  WRITE setToolbarWidth  NOTIFY toolbarWidthChanged)
		Q_PROPERTY(int toolbarHeight READ toolbarHeight WRITE setToolbarHeight NOTIFY toolbarHeightChanged)
		Q_PROPERTY(int explorerWidth  READ explorerWidth  WRITE setExplorerWidth  NOTIFY explorerWidthChanged)
		Q_PROPERTY(int explorerHeight READ explorerHeight WRITE setExplorerHeight NOTIFY explorerHeightChanged)
		Q_PROPERTY(int infoWidth  READ infoWidth  WRITE setInfoWidth  NOTIFY infoWidthChanged)
		Q_PROPERTY(int infoHeight READ infoHeight WRITE setInfoHeight NOTIFY infoHeightChanged)
		Q_PROPERTY(int editorWidth  READ editorWidth  WRITE setEditorWidth  NOTIFY editorWidthChanged)
		Q_PROPERTY(int editorHeight READ editorHeight WRITE setEditorHeight NOTIFY editorHeightChanged)


		Q_PROPERTY(int previewWidth  READ previewWidth  WRITE setPreviewWidth  NOTIFY previewWidthChanged)
		Q_PROPERTY(int previewHeight READ previewHeight WRITE setPreviewHeight NOTIFY previewHeightChanged)
		Q_PROPERTY(int logWidth  READ logWidth  WRITE setLogWidth  NOTIFY logWidthChanged)
		Q_PROPERTY(int logHeight READ logHeight WRITE setLogHeight NOTIFY logHeightChanged)
		
		Q_PROPERTY(int statusbarWidth  READ statusbarWidth  WRITE setStatusbarWidth  NOTIFY statusbarWidthChanged)
		Q_PROPERTY(int statusbarHeight READ statusbarHeight WRITE setStatusbarHeight NOTIFY statusbarHeightChanged)
		Q_PROPERTY(int borderFixedSize READ borderFixedSize WRITE setBorderFixedSize NOTIFY borderFixedSizeChanged)

private:
	Design();
	static Design* m_instance;
	Colors m_colors;
public:
	static Design* instance() {
		if (m_instance == nullptr) m_instance = new Design();
		return m_instance;
	}
	Colors c() { return m_colors; }

	const int MIM_WINDOW_WIDTH = 640;
	const int MIM_WINDOW_HEIGHT = 720;
	const int MAX_WINDOW_WIDTH = 1920;
	const int MAX_WINDOW_HEIGHT = 1080;

	int windowWidth() const { return m_windowWidth; }
	int windowHeight() const { return m_windowHeight; }
	int menubarWidth() const { return m_menubarWidth; }
	int menubarHeight() const { return m_menubarHeight; }
	int toolbarWidth() const { return m_toolbarWidth; }
	int toolbarHeight() const { return m_toolbarHeight; }
	int explorerWidth() const { return m_explorerWidth; }
	int explorerHeight() const { return m_explorerHeight; }
	int infoWidth() const { return m_infoWidth; }
	int infoHeight() const { return m_infoHeight; }
	int editorWidth() const { return m_editorWidth; }
	int editorHeight() const { return m_editorHeight; }


	int previewWidth() const { return m_previewWidth; }
	int previewHeight() const { return m_previewHeight; }
	int logWidth() const { return m_logWidth; }
	int logHeight() const { return m_logHeight; }
	
	int statusbarWidth() const  { return m_statusbarWidth; }
	int statusbarHeight() const { return m_statusbarHeight; }
	int borderFixedSize() const { return m_borderFixedSize; }
	int titleBarHeight() const { return m_titleBarHeight; }
	void initialize();

	public slots:
	int pt(int pixel) { return pixel * scaleFactor; }
	void setWindowWidth(const int &m) { m_windowWidth = m;  emit windowWidthChanged(); }
	void setWindowHeight(const int &m) { m_windowHeight = m; emit windowHeightChanged(); }
	void setMenubarWidth(const int &m) { m_menubarWidth = m; emit menubarWidthChanged(); }
	void setMenubarHeight(const int &m) { m_menubarHeight = m; emit menubarHeightChanged(); }
	void setToolbarWidth(const int &m) { m_toolbarWidth = m; emit toolbarWidthChanged(); }
	void setToolbarHeight(const int &m) { m_toolbarHeight = m; emit toolbarHeightChanged(); }
	void setExplorerWidth(const int &m) { m_explorerWidth = m; emit explorerWidthChanged(); }
	void setExplorerHeight(const int &m) { m_explorerHeight = m; emit explorerHeightChanged(); }
	void setInfoWidth(const int &m) { m_infoWidth = m; emit infoWidthChanged(); }
	void setInfoHeight(const int &m) { m_infoHeight = m; emit infoHeightChanged(); }
	void setEditorWidth(const int &m) { m_editorWidth = m; emit editorWidthChanged(); }
	void setEditorHeight(const int &m) { m_editorHeight = m; emit editorHeightChanged(); }

	void setPreviewWidth(const int &m) { m_previewWidth = m; emit previewWidthChanged(); }
	void setPreviewHeight(const int &m) { m_previewHeight = m; emit previewHeightChanged(); }
	void setLogWidth(const int &m) { m_logWidth = m; emit logWidthChanged(); }
	void setLogHeight(const int &m) { m_logHeight = m; emit logHeightChanged(); }
	
	void setStatusbarWidth(const int &m) { m_statusbarWidth = m; emit statusbarWidthChanged(); }
	void setStatusbarHeight(const int &m) { m_statusbarHeight = m; emit statusbarHeightChanged(); }
	void setBorderFixedSize(const int &m) { m_borderFixedSize = m; emit borderFixedSizeChanged(); }
	void setTitleBarHeight(const int &m) { m_titleBarHeight = m; }
signals:
	void windowWidthChanged();
	void windowHeightChanged();
	void menubarWidthChanged();
	void menubarHeightChanged();
	void toolbarWidthChanged();
	void toolbarHeightChanged();
	void infoWidthChanged();
	void infoHeightChanged();
	void editorWidthChanged();
	void editorHeightChanged();


	void explorerWidthChanged();
	void explorerHeightChanged();
	void previewWidthChanged();
	void previewHeightChanged();
	void logWidthChanged();
	void logHeightChanged();
	
	void statusbarWidthChanged();
	void statusbarHeightChanged();
	void borderFixedSizeChanged(); 
private:

	float scaleFactor = 1;
	int m_titleBarHeight;
	int m_windowWidth = MIM_WINDOW_WIDTH;
	int m_windowHeight = MIM_WINDOW_HEIGHT;	
	int m_menubarWidth = m_windowWidth;
	int m_menubarHeight = pt(58);
	int m_toolbarWidth;
	int m_toolbarHeight;
	int m_infoWidth;
	int m_infoHeight = 100;
	int m_editorWidth;
	int m_editorHeight;


	int m_statusbarWidth = m_windowWidth;
	int m_statusbarHeight = pt(30);
	
	int m_borderFixedSize = pt(8);
	
	int m_explorerWidth = 300;
	int m_explorerHeight = m_windowHeight - m_menubarHeight;
	
	int m_logWidth = m_previewWidth;
	int m_logHeight = pt(200);//m_explorerHeight - m_previewHeight;

	int m_previewWidth = m_windowWidth - m_explorerWidth - m_borderFixedSize;
	int m_previewHeight = /*m_explorerHeight * 2 / 3*/ m_explorerHeight - m_logHeight - m_borderFixedSize;
};
//extern Design D;

