import xml.etree.ElementTree as ET
import re
from math import modf

def convert_svg_to_custom_xml(input_file, output_file):
    namespaces = {
        'svg': 'http://www.w3.org/2000/svg',
        'inkscape': 'http://www.inkscape.org/namespaces/inkscape'
    }
    
    tree = ET.parse(input_file)
    root = tree.getroot()
    
    shapes = ET.Element('Shapes')
    
    for path in root.findall('.//svg:path', namespaces):
        style = path.get('style', '')
        label = path.get('{%s}label' % namespaces['inkscape'])
        d = path.get('d', '')
        
        style_props = dict(re.findall(r'([a-z-]+):([^;]+)', style))
        
        points, is_closed = parse_svg_path(d)
        
        path_elem = ET.SubElement(shapes, 'Path')
        if label:
            path_elem.set('name', label)
        path_elem.set('closed', 'true' if is_closed else 'false')
        
        for prop in ['stroke']:
            if prop in style_props:
                path_elem.set(prop, style_props[prop].strip())
        
        for x, y in points:
            point_elem = ET.SubElement(path_elem, 'Point')
            point_elem.set('x', f"{process_coord(x):.2f}")
            point_elem.set('y', f"{process_coord(y):.2f}")
    
    tree = ET.ElementTree(shapes)
    tree.write(output_file, encoding='utf-8', xml_declaration=True)

def process_coord(coord):
    abs_coord = abs(coord)
    rounded = round(abs_coord * 4) / 4
    return rounded

def parse_svg_path(d):
    commands = re.findall(r'([A-Za-z])([^A-Za-z]*)', d)
    points = []
    current_pos = (0.0, 0.0)
    start_pos = (0.0, 0.0)
    is_closed = False
    
    for cmd, args_str in commands:
        args = list(map(float, re.findall(r'[-+]?\d*\.?\d+(?:[eE][-+]?\d+)?', args_str)))
        relative = cmd.islower()
        cmd = cmd.upper()
        
        i = 0
        while i < len(args):
            if cmd == 'M':  # Moveto
                if len(args[i:]) < 2:
                    break
                x, y = args[i], args[i+1]
                if relative:
                    x += current_pos[0]
                    y += current_pos[1]
                current_pos = (x, y)
                start_pos = current_pos
                points.append(current_pos)
                i += 2
                # Последующие пары координат обрабатываем как Lineto
                cmd = 'L'
            
            elif cmd == 'L':  # Lineto
                if len(args[i:]) < 2:
                    break
                x, y = args[i], args[i+1]
                if relative:
                    x += current_pos[0]
                    y += current_pos[1]
                current_pos = (x, y)
                points.append(current_pos)
                i += 2
                
            elif cmd == 'H':  # Horizontal lineto
                if len(args[i:]) < 1:
                    break
                x = args[i]
                print(x)
                if relative:
                    x += current_pos[0]
                current_pos = (x, current_pos[1])
                points.append(current_pos)
                i += 1
                
            elif cmd == 'V':  # Vertical lineto
                if len(args[i:]) < 1:
                    break
                y = args[i]
                if relative:
                    y += current_pos[1]
                current_pos = (current_pos[0], y)
                points.append(current_pos)
                i += 1
                
            elif cmd == 'Z':  # Close path
                is_closed = True
                if points:
                    points.append(start_pos)
                i = len(args)  # Пропускаем оставшиеся аргументы
                
            else:
                i = len(args)
    
    return points, is_closed
convert_svg_to_custom_xml('mouse_inkscape_correct4.svg', 'mouse.xml')
