#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "MLRRTstarWindow.hpp"
#include "MLRRTstarConfig.hpp"

using namespace topologyPathPlanning::homotopy;

namespace topologyPathPlanning {

namespace tarrts {

MLRRTstarConfig::MLRRTstarConfig(MLRRTstarWindow * parent) {
  mpParentWindow = parent;

  mpCheckMinDist = new QCheckBox();
  if (mpParentWindow->mpViz->m_PPInfo.m_min_dist_enabled==true) {
    mpCheckMinDist->setChecked(true);
  }
  else {
    mpCheckMinDist->setChecked(false);
  }
  connect(mpCheckMinDist , SIGNAL(stateChanged(int)),this, SLOT(checkMinDistStateChange(int)));
  mpLabelMinDist = new QLabel("Minimize distance");

  mpLabelIterationNum = new QLabel("Iteration Num: ");
  mpLineEditIterationNum = new QLineEdit();
  mpLineEditIterationNum->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.m_max_iteration_num));
  mpLineEditIterationNum->setMaximumWidth(40);
  mpLabelSegmentLength = new QLabel("Segment Len: ");
  mpLineEditSegmentLength = new QLineEdit();
  mpLineEditSegmentLength->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.m_segment_length));
  mpLineEditSegmentLength->setMaximumWidth(40);

  mpLabelCost = new QLabel("Cost Map: ");
  mpLineEditCost = new QLineEdit();
  mpLineEditCost->setText(mpParentWindow->mpViz->m_PPInfo.m_objective_file);
  mpLineEditCost->setMaximumWidth(300);

  QHBoxLayout * minDistLayout = new QHBoxLayout();
  minDistLayout->addWidget(mpCheckMinDist);
  minDistLayout->addWidget(mpLabelMinDist);
  minDistLayout->addWidget(mpLabelIterationNum);
  minDistLayout->addWidget(mpLineEditIterationNum);
  minDistLayout->addWidget(mpLabelSegmentLength);
  minDistLayout->addWidget(mpLineEditSegmentLength);
  mpBtnAdd = new QPushButton(tr("Add"));
  connect(mpBtnAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
  
  mpCheckHomotopicEnforcement = new QCheckBox();
  if (mpParentWindow->mpViz->m_PPInfo.m_homotopic_enforcement==true) {
    mpCheckHomotopicEnforcement->setChecked(true);
  }
  else {
    mpCheckHomotopicEnforcement->setChecked(false);
  }
  mpLabelHomotopicEnforcement = new QLabel("Homotopic Enforcement");

  QHBoxLayout * paramConfigLayout = new QHBoxLayout();
  paramConfigLayout->addWidget(mpLabelHomotopicEnforcement);
  paramConfigLayout->addWidget(mpCheckHomotopicEnforcement);

  QHBoxLayout * costMapLayout = new QHBoxLayout();
  costMapLayout->addWidget(mpLabelCost);
  costMapLayout->addWidget(mpLineEditCost);
  costMapLayout->addWidget(mpBtnAdd);

  mpBtnOK = new QPushButton(tr("OK"));
  mpBtnCancel = new QPushButton(tr("Cancel"));
  connect(mpBtnOK, SIGNAL(clicked()), this, SLOT(onBtnOKClicked()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

  QHBoxLayout * buttonsLayout = new QHBoxLayout();
  buttonsLayout->addWidget(mpBtnOK);
  buttonsLayout->addWidget(mpBtnCancel);

  QVBoxLayout * mainLayout = new QVBoxLayout();
  mainLayout->addLayout(minDistLayout);
  mainLayout->addLayout(costMapLayout);
  mainLayout->addLayout(paramConfigLayout);
  mainLayout->addLayout(buttonsLayout);

  setWindowTitle("Config Objectives");

  setLayout(mainLayout);
}

void MLRRTstarConfig::onBtnOKClicked() {
  updateConfiguration();
  close();
}

void MLRRTstarConfig::onBtnCancelClicked() {
  close();
}

void MLRRTstarConfig::onBtnAddClicked() {
  QString objFilename = QFileDialog::getOpenFileName(this,
                 tr("Open Objective File"), "./", tr("Objective Files (*.*)"));
  if (objFilename!="") {
    if(true==isCompatible(objFilename)) {
      if(mpParentWindow->mpViz) {
        mpLineEditCost->setText(objFilename);
        repaint();
      }
    }
  }
  else {
    QMessageBox msg;
    msg.setText("Fitness distribution file is not compatible!");
    msg.exec();
  }
}


void MLRRTstarConfig::updateDisplay() {
  if(mpParentWindow) {
    if(mpParentWindow->mpViz) {
      if( mpParentWindow->mpViz->m_PPInfo.m_min_dist_enabled==true ) {
        mpCheckMinDist->setChecked(true);
      }
      else {
        mpCheckMinDist->setChecked(false);
      }
      if( mpParentWindow->mpViz->m_PPInfo.m_homotopic_enforcement==true ) {
        mpCheckHomotopicEnforcement->setChecked(true);
      }
      else {
        mpCheckHomotopicEnforcement->setChecked(false);
      }
      mpLineEditSegmentLength->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.m_segment_length));
      mpLineEditIterationNum->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.m_max_iteration_num));
      mpLineEditCost->setText(mpParentWindow->mpViz->m_PPInfo.m_objective_file);
    }
  }
}

void MLRRTstarConfig::updateConfiguration() {
  if (mpCheckMinDist->isChecked()==true) {
    mpParentWindow->mpViz->m_PPInfo.m_min_dist_enabled=true;
  }
  else {
    mpParentWindow->mpViz->m_PPInfo.m_min_dist_enabled=false;
  }
  if (mpCheckHomotopicEnforcement->isChecked()==true) {
    mpParentWindow->mpViz->m_PPInfo.m_homotopic_enforcement=true;
  }
  else {
    mpParentWindow->mpViz->m_PPInfo.m_homotopic_enforcement=false;
  }

  mpParentWindow->mpViz->m_PPInfo.m_objective_file = mpLineEditCost->text();
  mpParentWindow->mpViz->m_PPInfo.m_max_iteration_num = mpLineEditIterationNum->text().toInt();
    mpParentWindow->mpViz->m_PPInfo.m_segment_length = mpLineEditSegmentLength->text().toDouble();

}

bool MLRRTstarConfig::isCompatible(QString fitnessFile) {
  QPixmap pixmap(fitnessFile);
  if (pixmap.width()==mpParentWindow->mpViz->m_PPInfo.m_map_width
          && pixmap.height()==mpParentWindow->mpViz->m_PPInfo.m_map_height) {
    return true;
  }
  return false;
}

void MLRRTstarConfig::checkMinDistStateChange(int state) {
  if(mpCheckMinDist->checkState()==Qt::Checked) {
    mpLineEditCost->setEnabled(false);
    mpBtnAdd->setEnabled(false);
  }
  else {
    mpLineEditCost->setEnabled(true);
    mpBtnAdd->setEnabled(true);
  }
  repaint();
}

} // tarrts

} // topologyPathPlanning