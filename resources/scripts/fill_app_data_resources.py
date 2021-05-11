import os

cities = ["tuzhyliv1","vinnytsia", "dnipro","donetsk","zhytomyr","zaporizhzhia","ivano-frankivsk","kalush","kyiv", "kropyvnytskyi", "luhansk","lutsk","lviv","luhansk",
"odesa","poltava","rivne","sumy","ternopil","uzhorod","kharkiv","kherson","khmelnytskyi","сherkasy","chernivtsi","chernihiv"]

def create_city_resources():
    for city in cities:
        os.mkdir(city)
        file_name = city + "/description.txt"
        f = open(file_name, 'w+')
        f.close()

def fill_app_data_resource_file():
    f = open('../app_data.qrc', 'w')
    f.write('<RCC>\n')
    f.write('    <qresource prefix="/">\n')
    f.write('        <file>app_data/localities.json</file>\n')
    for city in cities:
        files = os.listdir('../app_data/localities_data/' + city)
        for file in files:
            f.write('        <file>app_data/localities_data/' + city + '/' + file + '</file>\n')
        f.write('\n')
    f.write('    </qresource>\n')
    f.write('</RCC>\n') 
    f.close()
        
if __name__ == "__main__":
    fill_app_data_resource_file()
