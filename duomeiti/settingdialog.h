#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
	class SettingDialog;
}

class GameConfig;
//弹出一个对话框 用于用户设置游戏参数
class SettingDialog : public QDialog{
	Q_OBJECT
public:
	explicit SettingDialog(QWidget *parent = 0);
private:
	//根据GameConfig初始化字段
	void initFields();
	Ui::SettingDialog* ui;
	GameConfig* m_gc;
	// QDialog interface
public slots:
	virtual void accept();
	virtual int exec();
private slots:
	void on_m_continueHit_toggled(bool checked);
	void on_m_continueHitNoTimeLimit_toggled(bool checked);
	void on_checkBox_clicked(bool checked);
};

#endif // SETTINGDIALOG_H
