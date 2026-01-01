#include "Invitation.hpp"

Invitation::Invitation(std::shared_ptr<User> invitee) : invitee(invitee), status(Pending) {}
std::shared_ptr<User> Invitation::getInvitee() const { return invitee; }
Invitation::Status Invitation::getStatus() const { return status; }
void Invitation::setStatus(Status s) { status = s; }
