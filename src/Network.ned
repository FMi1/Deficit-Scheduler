//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package projectpecsn;

//
// TODO auto-generated type
//
network Network
{
    parameters:
        bool exponentialDistribution = default(false);
        double TurnServiceRatio = default(1);
        double ServiceTime @unit(s) = default(1s);
        double Vacation @unit(s) = default(1s);
        double ro = default(0.8);

        @display("bgb=180.91,146.56");
    submodules:
        JobProducer: JobProducer {
            @display("p=48.853333,71.753334");
        }
        Server: Server {
            @display("p=126.71333,71.753334;is=vl");
        }
    connections:
        JobProducer.out --> Server.in;
}
