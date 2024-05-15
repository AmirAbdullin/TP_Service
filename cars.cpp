#include "cars.h"
#include "ui_cars.h"
#include "newto.h"

#include <Qt>

/**
 * @brief Конструктор класса cars.
 *
 * Инициализирует новый объект класса cars с заданным родительским виджетом.
 * Устанавливает размеры окна, конфигурирует интерфейс пользователя и подготавливает модели данных для работы с базой данных.
 *
 * @param parent Указатель на родительский виджет.
 */
cars::cars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cars)
{
    ui->setupUi(this);
    setFixedSize(800, 400);

    ui->carsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->carsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    query = new QSqlQuery(db);

    query->exec("CREATE TABLE Maint (ГРЗ TEXT NOT NULL, Работы TEXT NOT NULL, Стоимость TEXT NOT NULL, Комментарий TEXT NOT NULL, Дата TEXT NOT NULL, Пробег TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("Cars");
    model->select();

    ui->carsTable->setModel(model);
    ui->carsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    model2 = new QSqlTableModel(this, db);
    model2->setTable("Maint");
    model2->select();

    ui->oldRepairsTable->setModel(model2);
    ui->oldRepairsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    querymodel = new QSqlQueryModel;

    // Блокировка кнопок до выбора элемента в таблице
    ui->pushButton->setEnabled(false);
    ui->repairsListButton->setEnabled(false);
}

/**
 * @brief Деструктор класса cars.
 *
 * Освобождает все ресурсы, связанные с объектом и его элементами интерфейса.
 */
cars::~cars()
{
    delete ui;
}

/**
 * @brief Слот, реагирующий на нажатие кнопки выхода.
 *
 * Скрывает окно, эффективно закрывая его без завершения приложения.
 */
void cars::on_pushButton_3_clicked()
{
    hide();
}

/**
 * @brief Слот для создания нового технического обслуживания (ТО).
 *
 * Запускает диалоговое окно для создания нового ТО для выбранного автомобиля.
 * ГРЗ выбранного автомобиля передаётся в новое окно для дальнейшего использования.
 */
void cars::on_pushButton_clicked()
{
    QModelIndex currentIndex = ui->carsTable->currentIndex();
    QString grz = (ui->carsTable->model()->data(ui->carsTable->model()->index(currentIndex.row(),0), 0)).toString();

    hide();

    newto to;
    to.setGrz(grz); // Устанавливает Гос номер выбранного авто в новом окне
    to.setModal(true);
    to.exec();
}

/**
 * @brief Слот для отображения списка всех технических обслуживаний выбранного автомобиля.
 *
 * Выполняет запрос к базе данных для получения списка ТО выбранного автомобиля и обновляет модель данных для отображения.
 */
void cars::on_repairsListButton_clicked()
{
    QModelIndex currentIndex = ui->carsTable->currentIndex();
    QString grz = (ui->carsTable->model()->data(ui->carsTable->model()->index(currentIndex.row(),0), 0)).toString();

    querymodel->setQuery("SELECT * FROM Maint WHERE ГРЗ = '" + grz + "';");
    querymodel->setHeaderData(0, Qt::Horizontal, tr("Гос номер"));
    querymodel->setHeaderData(1, Qt::Horizontal, tr("Работы"));
    querymodel->setHeaderData(2, Qt::Horizontal, tr("Стоимость"));
    querymodel->setHeaderData(3, Qt::Horizontal, tr("Комментарий"));
    querymodel->setHeaderData(4, Qt::Horizontal, tr("Дата"));
    querymodel->setHeaderData(5, Qt::Horizontal, tr("Пробег"));

    ui->oldRepairsTable->setModel(querymodel);
}

/**
 * @brief Слот, активирующий кнопки управления.
 *
 * Разблокирует кнопки управления при выборе строки в таблице автомобилей.
 *
 * @param index Индекс выбранной строки в таблице.
 */
void cars::on_carsTable_clicked(const QModelIndex &index)
{
    ui->pushButton->setEnabled(true);
    ui->repairsListButton->setEnabled(true);
}
