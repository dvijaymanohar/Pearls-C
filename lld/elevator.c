

struct inputPanel;
struct directionPanel

struct floorObject {
    struct directionPanel directionIndicator;
    struct inputPanel input;
    u8 noOfFloor;
};

u8 getFloorNumber(struct floorObject *floor) {
    return floor->noOfFloor;
}

void display_direction(struct floorObject *floor, char direction) {
    floor->directionIndicator.direction = direction;
}

struct elevator {
    ---
    u8 postionOfElevator;
    u8 moveUpwardsRequests[9];
    u8 moveDownwardsRequests[9];

    struct floorObject[10];
    ---
}

void setElevatorRequest(u8 floorNumber) {

}


