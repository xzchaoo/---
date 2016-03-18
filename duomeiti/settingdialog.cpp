#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "gameconfig.h"

SettingDialog::SettingDialog(QWidget *parent) :
	QDialog(parent),ui(new Ui::SettingDialog){
	ui->setupUi (this);
	m_gc=GameConfig::getInstance ();
}

void SettingDialog::initFields(){
	
	QPoint rowAndCol=m_gc->rowAndCol ();
	
	ui->m_row->setMaximum (m_gc->getInt ("maxRow",20));
	ui->m_col->setMaximum (m_gc->getInt ("maxCol",20));
	
	ui->m_row->setValue (rowAndCol.x ());
	ui->m_col->setValue (rowAndCol.y ());
	
	ui->m_continueHit->setChecked (m_gc->continueHit ());
	
	ui->m_limitStep->setMaximum (m_gc->getInt ("maxLimitStep",10));
	ui->m_limitStep->setValue (m_gc->limitStep ());
	
	ui->m_continueHitNoTimeLimit->setChecked (m_gc->continueHitNoTimeLimit ());
	
	ui->m_playBGMOnStartup->setChecked (m_gc->playBGMOnStartup ());
	
	ui->m_mute->setChecked (m_gc->mute ());
	
	ui->m_gameTime->setMaximum (m_gc->getInt ("maxGameTime",360));
	ui->m_gameTime->setValue (m_gc->gameTime ());
	
	ui->m_notMusicWhenHitFail->setChecked (m_gc->noMusicWhenHitFail ());
	
	ui->m_continueHitInterval->setValue (m_gc->continueHitInterval ());
	
	ui->m_noInformationWhenStop->setChecked (m_gc->noInformationWhenStop ());
	
	
	ui->m_iconTypes->setMaximum (m_gc->iconLoader ()->size ());
	ui->m_iconTypes->setMinimum (2);
	ui->m_iconTypes->setValue (m_gc->iconTypes ());
	
	//ui->m_openingShowId->setValue (m_gc->openingShowId ());
	
	ui->checkBox->setChecked (m_gc->openingShowId ()==0);
	on_checkBox_clicked(m_gc->openingShowId ()==0);

}


void SettingDialog::accept(){
	QPoint rowAndCol(ui->m_row->value (),ui->m_col->value ());
	
	m_gc->setRowAndCol (rowAndCol);
	
	m_gc->setContinueHit (ui->m_continueHit->isChecked ());
	
	m_gc->setLimitStep (ui->m_limitStep->value ());
	
	m_gc->setContinueHitNoTimeLimit (ui->m_continueHitNoTimeLimit->isChecked ());
	
	m_gc->setPlayBGMOnStartup (ui->m_playBGMOnStartup->isChecked ());
	
	m_gc->setMute (ui->m_mute->isChecked ());
	
	m_gc->setGameTime (ui->m_gameTime->value ());
	
	m_gc->setNoMusicWhenHitFail (ui->m_notMusicWhenHitFail->isChecked ());
	
	m_gc->setContinueHitInterval (ui->m_continueHitInterval->value ());
	
	m_gc->setNoInformationWhenStop (ui->m_noInformationWhenStop->isChecked ());
	
	m_gc->setIconTypes (ui->m_iconTypes->value ());
	
	m_gc->setOpeningShowId (ui->m_openingShowId->value ());
	
	QDialog::accept ();
}

//ui界面上的逻辑 实现选项联动 持续连击 和 持续连击无限制的关系
void SettingDialog::on_m_continueHit_toggled(bool checked){
	if(!checked)
		ui->m_continueHitNoTimeLimit->setChecked (false);
}

void SettingDialog::on_m_continueHitNoTimeLimit_toggled(bool checked){
	if(checked)
		ui->m_continueHit->setChecked (true);
}



int SettingDialog::exec(){
	//初始化各个字段
	initFields ();
	return QDialog::exec ();
}

void SettingDialog::on_checkBox_clicked(bool checked){
	if(checked){
		ui->m_openingShowId->setEnabled (false);
		ui->m_openingShowId->setMinimum (0);
		ui->m_openingShowId->setValue (0);
	}else{
		ui->m_openingShowId->setEnabled (true);
		ui->m_openingShowId->setMinimum (1);
		ui->m_openingShowId->setValue (m_gc->openingShowId ());
	}
}
