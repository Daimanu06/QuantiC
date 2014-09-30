#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QRect>

/**
 * @class Settings
 * @ingroup Settings
 * @brief Convenient Settings class to manage users's settings of the application.
 *
 * Load settings from filesystem when the application starts and save them when the application terminates.
 * Send signals when one of the settings have changed.
 */
class Settings : public QObject {
	Q_OBJECT

	private:
		Settings();
		Settings(const Settings&)  = delete;
		Settings(      Settings&&) = delete;
		~Settings();
		Settings& operator = (const Settings&)  = delete;
		Settings& operator = (      Settings&&) = delete;

	public:
		static Settings& getInstance();

	private:
		QSettings qs;

	public:
		enum SymbolType   { S_ASCII, S_Unicode };
		enum PrefixPolicy { P_AllPrefixes, P_OnlyPow3, P_NoPrefixes };
		enum HomeLayout   { H_Grid, H_List };

	private:
		Q_PROPERTY(QRect window_geometry       READ windowGeometry        WRITE setWindowGeometry)
		Q_PROPERTY(bool  window_maximized      READ isWindowMaximized     WRITE setWindowMaximized)
		Q_PROPERTY(bool  window_geometry_saved READ isWindowGeometrySaved WRITE setWindowGeometrySaved)
		Q_PROPERTY(SymbolType symbol_type      READ symbolType            WRITE setSymbolType          NOTIFY symbolTypeChanged)
		Q_PROPERTY(PrefixPolicy prefix_policy  READ prefixPolicy          WRITE setPrefixPolicy        NOTIFY prefixPolicyChanged)
		Q_PROPERTY(HomeLayout home_layout      READ homeLayout            WRITE setHomeLayout          NOTIFY homeLayoutChanged)
		Q_PROPERTY(QString data_dir            READ dataDirectory         WRITE setDataDirectory       NOTIFY dataLocationChanged)

	signals:
		void symbolTypeChanged(SymbolType);
		void prefixPolicyChanged(PrefixPolicy);
		void homeLayoutChanged(HomeLayout);
		void dataLocationChanged(const QString &);
		void iconsLocationChanged(const QString &);

	public: //getters
		QRect windowGeometry() const;
		bool  isWindowMaximized() const;
		bool  isWindowGeometrySaved() const;
		SymbolType symbolType() const;
		PrefixPolicy prefixPolicy() const;
		HomeLayout homeLayout() const;
		QString dataDirectory() const;

	public slots: //setters
		void setWindowGeometry(const QRect &);
		void setWindowMaximized(bool);
		void setWindowGeometrySaved(bool);
		void setSymbolType(int);
		void setPrefixPolicy(int);
		void setHomeLayout(int);
		void setDataDirectory(const QString &);

	private:
		QRect window_geometry;
		bool  window_maximized;
		bool  window_geometry_saved;
		SymbolType symbol_type;
		PrefixPolicy prefix_policy;
		HomeLayout home_layout;
		QString data_dir;
		QString icons_location;

};

#endif // SETTINGS_H
