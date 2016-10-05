/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include "MarketForm.hpp"

#include "ContrModel.hpp"
#include "Utility.hpp"

#include <QAbstractItemModel>
#include <QApplication>
#include <QComboBox>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <memory>

using namespace std;

namespace swirly {
namespace ui {

MarketForm::MarketForm(ContrModel& contrModel, QWidget* parent, Qt::WindowFlags f)
  : QWidget{parent, f}, contrModel_(contrModel)
{
  auto contrComboBox = make_unique<QComboBox>();
  {
    auto del = makeDeleter(contrComboBox->model());
    contrComboBox->setModel(&contrModel);
  }
  QFontMetrics fm{QApplication::font()};
  contrComboBox->setMinimumWidth(fm.averageCharWidth() * 12);

  auto settlDateEdit = make_unique<QDateEdit>(QDate{2016, 10, 28});
  auto lotsEdit = make_unique<QLineEdit>();
  lotsEdit->setPlaceholderText(tr("Lots"));
  {
    auto del = makeDeleter(const_cast<QValidator*>(lotsEdit->validator()));
    lotsEdit->setValidator(&lotsValidator_);
  }
  auto priceEdit = make_unique<QLineEdit>();
  priceEdit->setPlaceholderText(tr("Price"));
  {
    auto del = makeDeleter(const_cast<QValidator*>(priceEdit->validator()));
    priceEdit->setValidator(&priceValidator_);
  }
  auto buyButton = make_unique<QPushButton>(tr("Buy"));
  auto sellButton = make_unique<QPushButton>(tr("Sell"));

  connect(contrComboBox.get(),
          static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
          &MarketForm::slotContrChanged);
  connect(buyButton.get(), &QPushButton::clicked,
          [this]() { this->slotBuyOrSellClicked(Side::Buy); });
  connect(sellButton.get(), &QPushButton::clicked,
          [this]() { this->slotBuyOrSellClicked(Side::Sell); });

  auto layout = make_unique<QHBoxLayout>();
  layout->addWidget(contrComboBox_ = contrComboBox.release());
  layout->addWidget(settlDateEdit_ = settlDateEdit.release());
  layout->addWidget(lotsEdit_ = lotsEdit.release());
  layout->addWidget(new QLabel{tr("@")});
  layout->addWidget(priceEdit_ = priceEdit.release());
  layout->addWidget(buyButton.release());
  layout->addWidget(sellButton.release());
  layout->addStretch(1);

  setLayout(layout.release());
}

MarketForm::~MarketForm() noexcept = default;

void MarketForm::slotContrChanged(int index)
{
  if (index < 0) {
    // No item selected.
    return;
  }
  auto contr = contrComboBox_->currentData().value<Contr>();
  qDebug() << "slotContrChanged:" << contr;
  lotsValidator_.setRange(unbox(contr.minLots()), unbox(contr.maxLots()));
  priceValidator_.setDecimals(contr.priceDp());
}

void MarketForm::slotBuyOrSellClicked(Side side)
{
  auto contr = contrComboBox_->currentData().value<Contr>();
  const auto lots = box<Lots>(lotsEdit_->text().toLongLong());
  const auto ticks = priceToTicks(priceEdit_->text().toDouble(), contr);
  emit createOrder(contr, settlDateEdit_->date(), "", side, lots, ticks);
}

} // ui
} // swirly
