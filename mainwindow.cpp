#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateComboBox();
    hideAllButtons();
    setWindowIcon(QIcon(":/images/sunset_icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete reply;
    delete manager;
}
void MainWindow::populateComboBox()
{
    countryCodes = {
        "AF - Afghanistan",
        "AL - Albania",
        "DZ - Algeria",
        "AS - American Samoa",
        "AD - Andorra",
        "AO - Angola",
        "AI - Anguilla",
        "AQ - Antarctica",
        "AR - Argentina",
        "AM - Armenia",
        "AW - Aruba",
        "AU - Australia",
        "AT - Austria",
        "AZ - Azerbaijan",
        "BS - Bahamas",
        "BH - Bahrain",
        "BD - Bangladesh",
        "BB - Barbados",
        "BY - Belarus",
        "BE - Belgium",
        "BZ - Belize",
        "BJ - Benin",
        "BM - Bermuda",
        "BT - Bhutan",
        "BO - Bolivia",
        "BQ - Bonaire, Sint Eustatius and Saba",
        "BA - Bosnia and Herzegovina",
        "BW - Botswana",
        "BV - Bouvet Island",
        "BR - Brazil",
        "IO - British Indian Ocean Territory",
        "BN - Brunei Darussalam",
        "BG - Bulgaria",
        "BF - Burkina Faso",
        "BI - Burundi",
        "CV - Cabo Verde",
        "KH - Cambodia",
        "CM - Cameroon",
        "CA - Canada",
        "KY - Cayman Islands",
        "CF - Central African Republic",
        "TD - Chad",
        "CL - Chile",
        "CN - China",
        "CX - Christmas Island",
        "CC - Cocos (Keeling) Islands",
        "CO - Colombia",
        "KM - Comoros",
        "CG - Congo",
        "CD - Congo (Democratic Republic of the)",
        "CK - Cook Islands",
        "CR - Costa Rica",
        "HR - Croatia",
        "CU - Cuba",
        "CW - Curaçao",
        "CY - Cyprus",
        "CZ - Czech Republic",
        "DK - Denmark",
        "DJ - Djibouti",
        "DM - Dominica",
        "DO - Dominican Republic",
        "EC - Ecuador",
        "EG - Egypt",
        "SV - El Salvador",
        "GQ - Equatorial Guinea",
        "ER - Eritrea",
        "EE - Estonia",
        "SZ - Eswatini",
        "ET - Ethiopia",
        "FK - Falkland Islands (Malvinas)",
        "FO - Faroe Islands",
        "FJ - Fiji",
        "FI - Finland",
        "FR - France",
        "GF - French Guiana",
        "PF - French Polynesia",
        "TF - French Southern Territories",
        "GA - Gabon",
        "GM - Gambia",
        "GE - Georgia",
        "DE - Germany",
        "GH - Ghana",
        "GI - Gibraltar",
        "GR - Greece",
        "GL - Greenland",
        "GD - Grenada",
        "GP - Guadeloupe",
        "GU - Guam",
        "GT - Guatemala",
        "GG - Guernsey",
        "GN - Guinea",
        "GW - Guinea-Bissau",
        "GY - Guyana",
        "HT - Haiti",
        "HM - Heard Island and McDonald Islands",
        "VA - Holy See (Vatican City State)",
        "HN - Honduras",
        "HK - Hong Kong",
        "HU - Hungary",
        "IS - Iceland",
        "IN - India",
        "ID - Indonesia",
        "IR - Iran (Islamic Republic of)",
        "IQ - Iraq",
        "IE - Ireland",
        "IM - Isle of Man",
        "IL - Israel",
        "IT - Italy",
        "JM - Jamaica",
        "JP - Japan",
        "JE - Jersey",
        "JO - Jordan",
        "KZ - Kazakhstan",
        "KE - Kenya",
        "KI - Kiribati",
        "KP - Korea (Democratic People's Republic of)",
        "KR - Korea (Republic of)",
        "KW - Kuwait",
        "KG - Kyrgyzstan",
        "LA - Lao People's Democratic Republic",
        "LV - Latvia",
        "LB - Lebanon",
        "LS - Lesotho",
        "LR - Liberia",
        "LY - Libya",
        "LI - Liechtenstein",
        "LT - Lithuania",
        "LU - Luxembourg",
        "MO - Macao",
        "MG - Madagascar",
        "MW - Malawi",
        "MY - Malaysia",
        "MV - Maldives",
        "ML - Mali",
        "MT - Malta",
        "MH - Marshall Islands",
        "MQ - Martinique",
        "MR - Mauritania",
        "MU - Mauritius",
        "YT - Mayotte",
        "MX - Mexico",
        "FM - Micronesia (Federated States of)",
        "MD - Moldova (Republic of)",
        "MC - Monaco",
        "MN - Mongolia",
        "ME - Montenegro",
        "MS - Montserrat",
        "MA - Morocco",
        "MZ - Mozambique",
        "MM - Myanmar",
        "NA - Namibia",
        "NR - Nauru",
        "NP - Nepal",
        "NL - Netherlands",
        "NC - New Caledonia",
        "NZ - New Zealand",
        "NI - Nicaragua",
        "NE - Niger",
        "NG - Nigeria",
        "NU - Niue",
        "NF - Norfolk Island",
        "MK - North Macedonia",
        "MP - Northern Mariana Islands",
        "NO - Norway",
        "OM - Oman",
        "PK - Pakistan",
        "PW - Palau",
        "PS - Palestine, State of",
        "PA - Panama",
        "PG - Papua New Guinea",
        "PY - Paraguay",
        "PE - Peru",
        "PH - Philippines",
        "PN - Pitcairn",
        "PL - Poland",
        "PT - Portugal",
        "PR - Puerto Rico",
        "QA - Qatar",
        "RE - Réunion",
        "RO - Romania",
        "RU - Russian Federation",
        "RW - Rwanda",
        "BL - Saint Barthélemy",
        "SH - Saint Helena, Ascension and Tristan da Cunha",
        "KN - Saint Kitts and Nevis",
        "LC - Saint Lucia",
        "MF - Saint Martin (French part)",
        "PM - Saint Pierre and Miquelon",
        "VC - Saint Vincent and the Grenadines",
        "WS - Samoa",
        "SM - San Marino",
        "ST - Sao Tome and Principe",
        "SA - Saudi Arabia",
        "SN - Senegal",
        "RS - Serbia",
        "SC - Seychelles",
        "SL - Sierra Leone",
        "SG - Singapore",
        "SX - Sint Maarten (Dutch part)",
        "SK - Slovakia",
        "SI - Slovenia",
        "SB - Solomon Islands",
        "SO - Somalia",
        "ZA - South Africa",
        "GS - South Georgia and the South Sandwich Islands",
        "SS - South Sudan",
        "ES - Spain",
        "LK - Sri Lanka",
        "SD - Sudan",
        "SR - Suriname",
        "SJ - Svalbard and Jan Mayen",
        "SE - Sweden",
        "CH - Switzerland",
        "SY - Syrian Arab Republic",
        "TW - Taiwan, Province of China",
        "TJ - Tajikistan",
        "TZ - Tanzania, United Republic of",
        "TH - Thailand",
        "TL - Timor-Leste",
        "TG - Togo",
        "TK - Tokelau",
        "TO - Tonga",
        "TT - Trinidad and Tobago",
        "TN - Tunisia",
        "TR - Turkey",
        "TM - Turkmenistan",
        "TC - Turks and Caicos Islands",
        "TV - Tuvalu",
        "UG - Uganda",
        "UA - Ukraine",
        "AE - United Arab Emirates",
        "GB - United Kingdom of Great Britain and Northern Ireland",
        "US - United States of America",
        "UY - Uruguay",
        "UZ - Uzbekistan",
        "VU - Vanuatu",
        "VE - Venezuela (Bolivarian Republic of)",
        "VN - Viet Nam",
        "WF - Wallis and Futuna",
        "EH - Western Sahara",
        "YE - Yemen",
        "ZM - Zambia",
        "ZW - Zimbabwe"
    };

    ui->cmbBox->addItems(countryCodes);
}


int MainWindow::getWeatherData()
{
    qDebug() << "in getWeatherData()";

    QString zipCode,countryCode, apiKey;

    zipCode = ui->txtZipCode->text();
    apiKey = "b3d4f8f3114decb4f42ff7865ba980f7"; //Please replace this apiKey by yours by creating a free account on api.openweathermap.org
    QStringList parts = ui->cmbBox->currentText().split("-");
    countryCode = parts[0].trimmed();

    manager = new QNetworkAccessManager(this);

    // Create the API URL with the zip code, country code, and API key
    QString url = QString("https://api.openweathermap.org/data/2.5/weather?zip=%1,%2&appid=%3")
                      .arg(zipCode)
                      .arg(countryCode)
                      .arg(apiKey);

    QNetworkRequest request((QUrl(url)));
    qDebug() << request.url();
    QByteArray byteArray;

    // Send the request
    reply = manager->get(request);

    // Connect the reply finished signal to a slot to process the result
    connect(reply, &QNetworkReply::finished, this, &MainWindow::onWeatherDataReceived);


    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network Error:" << reply->errorString();
        QMessageBox  msgBox;
        msgBox.setText("No Data Found!");
        msgBox.exec();
        return -1; // Exit if there is an error
    }

    return 0;
}

void MainWindow::onWeatherDataReceived()
{
    qDebug() << "in onWeatherDataReceived()";
    // Get the reply object
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    // Check for network errors
    if (reply->error() == QNetworkReply::NoError) {
        // Read the data from the reply
        QByteArray responseData = reply->readAll();
        showAllButtons();

        // Parse the JSON response
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();
        QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);

        // Extract data from the JSON response (e.g., weather description)
        QString weatherDescription = jsonObj["weather"].toArray()[0].toObject()["description"].toString();
        int weatherConditionCode = jsonObj["weather"].toArray()[0].toObject()["id"].toInt();

        double windSpeed = jsonObj["wind"].toObject()["speed"].toDouble();
        QString city = jsonObj["name"].toString();
        double temp = jsonObj["main"].toObject()["temp"].toDouble() - 273.15;
        double temp_max = jsonObj["main"].toObject()["temp_max"].toDouble() - 273.15;
        double temp_min = jsonObj["main"].toObject()["temp_min"].toDouble() - 273.15;
        double feels_like = jsonObj["main"].toObject()["feels_like"].toDouble() - 273.15;
        double humidity = jsonObj["main"].toObject()["humidity"].toDouble();
        QString Country = jsonObj["sys"].toObject()["country"].toString();
        qDebug() << "Weather description:" << weatherDescription;
        qDebug() << "windSpeed:" << windSpeed;
        qDebug() << "city:" << city;
        qDebug() << "temp:" << temp;
        qDebug() << "temp_max:" << temp_max;
        qDebug() << "temp_min:" << temp_min;
        ui->lbltemprature->setText(QString::number(temp));
        ui->lblWind->setText(QString::number(windSpeed));
        ui->lblRealFeel->setText(QString::number(feels_like));
        ui->lblDescription->setText(weatherDescription);
        ui->lblCity->setText(city);
        ui->lblCountryName->setText(Country);
        ui->lblHumidity->setText(QString::number(humidity));


        qDebug() <<  jsonString;
        ui->txtDetails->setText(jsonString);
        ui->txtDetails->hide();

        showWeatherLogo(weatherConditionCode);

        // You can extract other data like temperature, humidity, etc.
    } else {
        // Handle errors
        qDebug() << "Error:" << reply->errorString();
        QString msg;

        if(reply->errorString().contains("Host requires authentication"))
            msg = "Please make sure appid is valid.";

        QMessageBox  msgBox;
        msgBox.setText("No Data Found! \n" + reply->errorString() + "\n" + msg);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        hideAllButtons();
    }

    // Free the memory of the reply object
    reply->deleteLater();
}

void MainWindow::on_btnGo_clicked()
{

    getWeatherData();

}

void MainWindow::on_btnMoreDetails_clicked()
{
    if(ui->txtDetails->isVisible())
        ui->txtDetails->hide();
    else
        ui->txtDetails->show();
}

void MainWindow::hideAllButtons()
{
    ui->txtDetails->hide();
    ui->groupBox->hide();
    ui->btnMoreDetails->hide();    
}

void MainWindow::showAllButtons()
{
    ui->txtDetails->show();
    ui->groupBox->show();
    ui->btnMoreDetails->show();
}

void MainWindow::showWeatherLogo(int weatherConditionCode)
{
    QString imageName;

    switch(weatherConditionCode)
    {
    case  200: imageName = "Thunderstorm_with_light_rain.png";break;
    case 201: imageName = "Thunderstorm_with_rain.png";break;
    case 202: imageName = "Thunderstorm_with_heavy_rain.png";break;
    case 210: imageName = "Light_thunderstorm.png";break;
    case 211: imageName = "Thunderstorm.png";break;
    case 212: imageName = "Heavy_thunderstorm.png";break;
    case 221: imageName = "Ragged_thunderstorm.png";break;
    case 230: imageName = "Thunderstorm_with_light_drizzle.png";break;
    case 231: imageName = "Thunderstorm_with_drizzle.png";break;
    case 232: imageName = "Thunderstorm_with_heavy_drizzle.png";break;

    case 300: imageName = "Light_intensity_drizzle.png";break;
    case 301: imageName = "Drizzle.png";break;
    case 302: imageName = "Heavy_intensity_drizzle.png";break;
    case 310: imageName = "Light_intensity_drizzle rain.png";break;
    case 311: imageName = "Drizzle_rain.png";break;
    case 312: imageName = "Heavy_intensity_drizzle_rain.png";break;
    case 313: imageName = "Shower_rain_and_drizzle.png";break;
    case 314: imageName = "Heavy_shower_rain_and_drizzle.png";break;
    case 321: imageName = "Shower_drizzle.png";break;

    case 500: imageName = "Light_rain.png";break;
    case 501: imageName = "Moderate_rain.png";break;
    case 502: imageName = "Heavy_intensity_rain.png";break;
    case 503: imageName = "Very_heavy_rain.png";break;
    case 504: imageName = "Extreme_rain.png";break;
    case 511: imageName = "Freezing_rain.png";break;
    case 520: imageName = "Light_intensity_shower_rain.png";break;
    case 521: imageName = "Shower_rain.png";break;
    case 522: imageName = "Heavy_intensity_shower_rain.png";break;
    case 531: imageName = "Ragged_shower_rain.png";break;

    case 600: imageName = "Light_snow.png";break;
    case 601: imageName = "Snow.png";break;
    case 602: imageName = "Heavy_snow.png";break;
    case 611: imageName = "Sleet.png";break;
    case 612: imageName = "Light_shower_sleet.png";break;
    case 613: imageName = "Shower_sleet.png";break;
    case 615: imageName = "Light_rain_and_snow.png";break;
    case 616: imageName = "Rain_and_snow.png";break;
    case 620: imageName = "Light_shower_snow.png";break;
    case 621: imageName = "Shower_snow.png";break;
    case 622: imageName = "Heavy_shower_snow.png";break;

    case 701: imageName = "Mist.png";break;
    case 711: imageName = "Smoke.png";break;
    case 721: imageName = "Haze.png";break;
    case 731: imageName = "Sand/dust whirls.png";break;
    case 741: imageName = "Fog.png";break;
    case 751: imageName = "Sand.png";break;
    case 761: imageName = "Dust.png";break;
    case 762: imageName = "Volcanic ash.png";break;
    case 771: imageName = "Squalls.png";break;
    case 781: imageName = "Tornado.png";break;
    case 800: imageName = "Clear_sky.png"; break;
    case 801: imageName = "Few_clouds.png"; break;         // (11-25%)
    case 802: imageName = "Scattered_clouds.png"; break;   // (25-50%)
    case 803: imageName = "Broken_clouds.png"; break;      // (51-84%)
    case 804: imageName = "Overcast_clouds.png"; break;    // (85-100%)

    }

    ui->lblWeatherLogo->setPixmap(":/images/" + imageName);
}
