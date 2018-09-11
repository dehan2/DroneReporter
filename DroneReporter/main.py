from time import *
from dronekit import *
import os.path


MAV_MODE_AUTO = 4


def commander(drones_set):
    while True:
        command = raw_input('commander?: ')
        command_to_drone(command, drones_set)


def command_to_drone(command, drones_set):
    if command == 'arm':
        arming_thread_list = list()
        for drone in drones_set:
            arming_thread = Thread(target=arming, args=drone)
            arming_thread_list.append(arming_thread)
        for arming_thread in arming_thread_list:
            arming_thread.start()
        for arming_thread in arming_thread_list:
            arming_thread.join()
    elif command == 'takeoff':
        tko_thread_list = list()
        for drone in drones_set:
            tko_thread = Thread(target=px4_set_take_off, args=drone)
            tko_thread_list.append(tko_thread)
        for tko_thread in tko_thread_list:
            tko_thread.start()
        for tko_thread in tko_thread_list:
            tko_thread.join() 
    elif command == 'report': 
        reportThread = Thread(target=write_status_file, args=drones_set)
        reportThread.start()

    elif command == 'gps':
        move_thread_list = list()
        for drone in drones_set:
            move_thread = Thread(target=get_gps, args=drone)
            move_thread_list.append(move_thread)
        for move_thread in move_thread_list:
            move_thread.start()
    elif command == 'south':
        move_thread_list = list()
        for drone in drones_set:
            move_thread = Thread(target=px4_go_to_south, args=drone)
            move_thread_list.append(move_thread)
        for move_thread in move_thread_list:
            move_thread.start()
        for move_thread in move_thread_list:
            move_thread.join()
    elif command == 'east':
        move_thread_list = list()
        for drone in drones_set:
            move_thread = Thread(target=px4_go_to_east, args=drone)
            move_thread_list.append(move_thread)
        for move_thread in move_thread_list:
            move_thread.start()
        for move_thread in move_thread_list:
            move_thread.join()
    elif command == 'west':
        move_thread_list = list()
        for drone in drones_set:
            move_thread = Thread(target=px4_go_to_west, args=drone)
            move_thread_list.append(move_thread)
        for move_thread in move_thread_list:
            move_thread.start()
        for move_thread in move_thread_list:
            move_thread.join()
    elif command == 'auto':
        print command
        mode_change_thread_list = list()
        for drone in drones_set:
            mode_change_thread = Thread(target=px4_set_auto, args=drone)
            mode_change_thread_list.append(mode_change_thread)
        for mode_change_thread in mode_change_thread_list:
            mode_change_thread.start()
        for mode_change_thread in mode_change_thread_list:
            mode_change_thread.join()
    elif command == 'land':
        land_change_thread_list = list()
        for drone in drones_set:
            land_change_thread = Thread(target=px4_set_land, args=drone)
            land_change_thread_list.append(land_change_thread)
        for land_change_thread in land_change_thread_list:
            land_change_thread.start()
        for land_change_thread in land_change_thread_list:
            land_change_thread.join()
    else:
        print 'arm, takeoff, auto, land is able'


def arming(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    this_sequence = drone[2]
    if this_sequence is not 0:
        sleep_time = 5*int(this_sequence)
	print sleep_time
	sleep(sleep_time)
    print str(this_port) + ' try to arming'
    while this_drone.armed is False:
        this_drone.armed = True
        sleep(1)
    print str(this_port) + ' is arming'


def px4_set_take_off(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    this_drone._master.mav.command_long_send(
        this_drone._master.target_system,
        this_drone._master.target_component,
        mavutil.mavlink.MAV_CMD_NAV_TAKEOFF,
        0, 0, 0, 0, 0, this_drone.location.global_frame.lat, this_drone.location.global_frame.lon, 5)
    sleep(0.1)
    print str(this_port) + '%s` takeoff ...' % this_drone.mode.name
    this_drone._master.mav.command_long_send(
        this_drone._master.target_system,
        this_drone._master.target_component,
        mavutil.mavlink.MAV_CMD_NAV_LOITER_TO_ALT,
        0, 0, 0, 0, 0, this_drone.location.global_frame.lat, this_drone.location.global_frame.lon, 5)
    sleep(0.1)
    print str(this_port) + '%s` takeoff ...' % this_drone.mode.name

    
def write_status_file(*drones_set):
    
    while True:
        if os.path.isfile('lock.txt') == False:
            lockFile = open("lock.txt", 'w')

            statusFile = open("status.txt", 'w')
            for drone in drones_set:
                this_drone = drone[0]
                this_port = drone[1]

                modeStr = this_drone.mode.name
                batteryStr = this_drone.battery.level
                latStr = this_drone.location.global_frame.lat
                lonStr = this_drone.location.global_frame.lon
                altStr = this_drone.location.global_frame.alt

                data = str(this_port) + ' ' + str(modeStr) + ' ' + str(batteryStr) + ' ' + str(latStr) + ' ' + str(lonStr) + ' ' + str(altStr) + '\n'       
                statusFile.write(data)

            statusFile.close()
            lockFile.close()
            os.remove('lock.txt')

        sleep(5)



def get_gps(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    print str(this_port) + ' Mode: %s' % this_drone.mode.name
    print str(this_port) + '`s %s`  ...' % this_drone.gps_0
    f = open(str(this_port) + "_GPS.txt", 'w')
    time = 1

    while True:
        data = str(time) + '- ' + str(this_drone.location.global_frame.lat) + ' ' + str(this_drone.location.global_frame.lon) + ' ' + str(this_drone.location.global_frame.alt) + '\n'
        print data
        f.write(data)
        time+=1
        sleep(1)
    

def px4_go_to_north(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    this_drone._master.mav.command_long_send(
        this_drone._master.target_system,
        this_drone._master.target_component,
        mavutil.mavlink.MAV_CMD_NAV_LOITER_TO_ALT,
        0, 0, 0, 0, 0, this_drone.location.global_frame.lat, this_drone.location.global_frame.lon, 5)
    print str(this_port) + '%s` go to north ...' % this_drone.mode.name


def px4_go_to_south(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    this_drone._master.mav.command_long_send(
        this_drone._master.target_system,
        this_drone._master.target_component,
        mavutil.mavlink.MAV_GOTO_DO_HOLD,
        0, 0, 0, 0, 0, this_drone.location.global_frame.lat-0.00001, this_drone.location.global_frame.lon, this_drone.location.global_frame.alt+10)
    print str(this_port) + '%s` go to south ...' % this_drone.mode.name

def px4_go_to_east(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    print str(this_port) + '%s` go to east ...' % this_drone.last_heartbeat

def px4_go_to_west(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    this_drone._master.mav.command_long_send(
        this_drone._master.target_system,
        this_drone._master.target_component,
        mavutil.mavlink.MAV_CMD_DO_REPOSITION,
        0, 0, 0, 0, 0, this_drone.location.global_frame.lat, this_drone.location.global_frame.lon-0.00001, this_drone.location.global_frame.alt)
    print str(this_port) + '%s` go to west ...' % this_drone.mode.name

"""
def arming_checker(*drones_set):
    checker_lock = threading.Lock()
    checker_lock.acquire()
    drones_status = [False] * len(drones_set)
    for i_drone in range(len(drones_set)):
        drone = drones_set[i_drone][0]
        if drone.armed is True:
            drones_status[i_drone] = True

    if drones_status.count(True) is len(drones_set):
        print '1-d'
        checker_lock.release()
        return True
    else:
        print '1-e'
        checker_lock.release()
        return False
"""


def px4_set_auto(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    while this_drone.mode.name is not 'MISSION':
        this_drone._master.mav.command_long_send(this_drone._master.target_system, this_drone._master.target_component,
                                               mavutil.mavlink.MAV_CMD_DO_SET_MODE, 0,
                                               MAV_MODE_AUTO,
                                               0, 0, 0, 0, 0, 0)
        sleep(1)
    print str(this_port) + ' Mode: %s' % this_drone.mode.name


def px4_set_land(*drone):
    this_drone = drone[0]
    this_port = drone[1]
    while this_drone.mode.name is not 'LAND':
        this_drone._master.mav.command_long_send(
            this_drone._master.target_system,
            this_drone._master.target_component,
            mavutil.mavlink.MAV_CMD_NAV_LAND,
            0, 0, 0, 0, 0, 0, 0, 0)
        sleep(1)
    print str(this_port) + '%s ...' % this_drone.mode.name


def read_data():
    file_name = raw_input('input file: ')
    port_file = open(file_name, 'r')
    lines = port_file.readlines()
    return_data = list()
    for line in lines:
        return_data.append(line)
    return return_data


if __name__ == "__main__":
    var_drones_set = list()

    input_data = read_data()
    input_port = raw_input('port?(if 1, localhost others 192.168.0.n): ')
    if input_port == '0':
        for input_datum in input_data:
            port_num = input_datum[0:5]
            start_sequence = input_datum[6]
            # drones_set is list of drone-tuple(vehicle, port)
            var_drones_set.append((connect('0.0.0.0:' + str(port_num)), port_num, start_sequence))

    else:
        for input_datum in input_data:
            port_num = input_datum[0:5]
            start_sequence = input_datum[6]
            # drones_set is list of drone-tuple(vehicle, port)
            print str(input_port) + ' try to connect ... ' 
            print '192.168.0.' + str(input_port) + ':' + str(port_num) + ' try to connect'
            var_drones_set.append((connect('192.168.0.' + str(input_port) + ':' + str(port_num)), port_num, start_sequence))

    print str(len(var_drones_set)) + ' drones connected'
    print var_drones_set
    commander_thread = Thread(target=commander, args=[var_drones_set])
    commander_thread.start()
