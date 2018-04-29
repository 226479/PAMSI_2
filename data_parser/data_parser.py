import xml.etree.ElementTree as ET
import os


def xml_finder():
    xml_path = []
    for root, __, files in os.walk("."):
        for xml_file in files:
            if xml_file.endswith(".xml"):
                xml_path.append(os.path.join(root, xml_file))
    return xml_path


def parse_xml():
    i = 1;
    for xml_file in xml_finder():
        with open(xml_file) as __:
            tree = ET.parse(xml_file)
            root = tree.getroot()
            for nazwa in root.iter('linia'):
                nazwaa = nazwa.get('nazwa')
            for wariant in root.iter('wariant'):
                output_file = open("../data_trams/" + str(i) + ".csv", "w")
                output_file.write(nazwaa)
                output_file.write("\n")
                for przystanek in wariant.iter('przystanek'):
                    output_file.write(przystanek.get('id') + ',')
                    output_file.write(przystanek.get('nazwa') + ',')
                    output_file.write(przystanek.get('ulica') + ',')
                    for tabliczka in przystanek.iter('tabliczka'):
                        output_file.write(tabliczka.get('mc') + ',\n')
                output_file.write("0")
                i=i+1
                print(i)
            output_file.close()

parse_xml()
