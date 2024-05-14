#include "admincars.h"
#include "ui_admincars.h"
#include "carinfo.h"
#include "newcar.h"

/**
 * @class adminCars
 * @brief Класс для управления интерфейсом администратора, позволяющий просматривать, регистрировать и удалять автомобили.
 *
 * Класс adminCars предоставляет функционал для управления списком автомобилей,
 * просмотра детальной информации о каждом автомобиле, а также регистрации и удаления автомобилей из базы данных.
 */
adminCars::adminCars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminCars)
{
    ui->setupUi(this);
    setFixedSize(800, 400);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    query = new QSqlQuery(db);

    model = new QSqlTableModel(this, db);
    model->setTable("Cars");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->moreButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}

adminCars::~adminCars()
{
    delete ui;
}

/**
 * @brief Выход из текущего окна.
 */
void adminCars::on_pushButton_3_clicked()
{
    hide();
}

/**
 * @brief Открывает окно с информацией о выбранном автомобиле.
 */
void adminCars::on_moreButton_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QString grz = (ui->tableView->model()->data(ui->tableView->model()->index(currentIndex.row(),0), 0)).toString();
    QString vin = (ui->tableView->model()->data(ui->tableView->model()->index(currentIndex.row(),1), 0)).toString();
    QString mileage = (ui->tableView->model()->data(ui->tableView->model()->index(currentIndex.row(),2), 0)).toString();

    carInfo inf;
    inf.setGrz(grz, vin, mileage);
    inf.updateTable();
    inf.setModal(true);
    inf.exec();

    ui->moreButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}

/**
 * @brief Открывает окно для регистрации нового автомобиля.
 */
void adminCars::on_pushButton_clicked()
{
    hide();
    newCar car;
    car.setModal(true);
    car.exec();
}

/**
 * @brief Разблокирует кнопки управления автомобилями при выборе строки в таблице.
 */
void adminCars::on_tableView_clicked(const QModelIndex &index)
{
    ui->moreButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}

/**
 * @brief Удаляет выбранный автомобиль и связанные с ним записи технического обслуживания.
 */
void adminCars::on_pushButton_2_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QString grz = (ui->tableView->model()->data(ui->tableView->model()->index(currentIndex.row(),0), 0)).toString();

    query->exec("DELETE FROM Cars WHERE ГРЗ = '"+grz+"';");
    query->exec("DELETE FROM Maint WHERE ГРЗ = '"+grz+"';");

    model->setTable("Cars");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->moreButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}
