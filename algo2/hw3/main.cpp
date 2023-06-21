#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <iomanip>

struct Session {      // session struct to store info we got from daily_schedule, availability_intervals.txt and capacity.txt
    std::string place;
    std::string saloon; 
    int cap;       
    int start;  
    int end; 
    Session(){}
    Session(std::string p, std::string sal, int c, int st, int e){
        place = p;
        saloon = sal;
        cap = c;
        start = st;
        end = e;
    }
    Session(std::string p, int c, int st=-1, int e=-1){
        place = p;
        cap = c;
        start = st;
        end = e;
    }
    void setStart(int in){start = in;};
};
 
struct Asset {       // Asset struct to keep assets.txt inofrmation
    std::string name;        
    int price;  
    float value;    
    Asset(){}
    Asset(std::string n, int p, float v){
        name = n;
        price = p;
        value = v;
    }
};

std::vector<int> p;
std::vector<int> mem;
std::vector<Session> sessions;
std::vector<Session> sessions_tow; // for best_for_eachplace

std::vector<Session> places; // for best_tour

std::vector<Asset> selectedItems; // for upgrade_list

std::vector<std::string> months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

void knap_sack(int W, int n, std::vector<Asset> list, std::ofstream & output) { //kanpsack algorithm from slides

    if (n <= 0 || W <= 0) return;

    std::vector<std::vector<float>> K(W+1, std::vector<float>(n+1, 0));
    std::vector<std::vector<bool>> selected(W+1, std::vector<bool>(n+1, false));

    float temp;
    for(int x = 1; x <= W; x++) {
        for(int j = 1; j <= n; j++) {
            K[x][j] = K[x][j-1];
            if(list[j-1].price <= x) {
                temp = K[x - list[j-1].price][j-1] + list[j-1].value;
                if (temp > K[x][j]) {
                    K[x][j] = temp;
                    selected[x][j] = true; // added selected vector to then write selected items to buy
                }
            }
        }
    }

    // Backtrack to find selected items
    int x = W;
    int j = n;
    while(j > 0 && x > 0){
        if(selected[x][j]){
            selectedItems.push_back(list[j-1]);
            x -= list[j-1].price;
        }
        j--;
    }

    output << "Total Value --> " << K[W][n] << std::endl;
    for (const Asset& item : selectedItems)
        output << item.name << std::endl;

    return;
}


int m_compute_opt(int i){
    if(mem[i+1] == -1) mem[i+1] = std::max(m_compute_opt(i-1), sessions[i].cap + m_compute_opt(p[i]));
    
    return mem[i+1];
}

int top_down(std::ofstream & output){ // top down weighted interval scheduling algorithm from slides
    sort(sessions.begin(), sessions.end(),[](Session &x, Session &y){return x.end < y.end;});
    int n = sessions.size();

    if(n == 0)return 0;

    p.resize(n);
    p = std::vector<int>(n, -1);
    mem.resize(n+1);
    mem = std::vector<int>(n+1, -1);

    // calculate p[i]
    for(int i = 1; i < n; i++) for(int j = 0; j < i; j++) if(sessions[j].end <= sessions[i].start) p[i] = j;

    mem[0] = 0;

    output << sessions[0].place << " --> ";
    return m_compute_opt(n-1);
}

int m_compute_opt_tour(int i){
    if(mem[i+1] == -1) mem[i+1] = std::max(m_compute_opt_tour(i-1), places[i].cap + m_compute_opt_tour(p[i]));
    
    return mem[i+1];
}

int top_down_tour(std::ofstream & output){ // weighted interval scheduling algorithm from slides but to calculate best_tour
    sort(places.begin(), places.end(),[](Session &x, Session &y){return x.end < y.end;});
    int n = places.size();
    
    if(n == 0)return 0;

    p.resize(n);
    p = std::vector<int>(n, -1);
    mem.resize(n+1);
    mem = std::vector<int>(n+1, -1);

    // calculate p[i]
    for(int i = 1; i < n; i++) for(int j = 0; j < i; j++) if(places[j].end <= places[i].start) p[i] = j;

    mem[0] = 0;

    output << "Total Revenue --> ";
    return m_compute_opt_tour(n-1);
}

void write_sessions(Session session, std::ofstream & output){ // write sessions to best_for_eachplace.txt
    int hour, min;
    std::replace(session.saloon.begin(), session.saloon.end(), '_', '-');
    output << std::left << std::setw(16) << session.place;
    output << std::setw(12) << session.saloon;

    hour = session.start/60;
    min = session.start - hour * 60;
    if(hour < 10){
        output << hour << ":"; 
        if(min < 10) output << "0" << min << "    ";
        else output << min << "   ";
    } 
    else{
        output << hour << ":";
        if(min < 10) output << "0" << min << "   ";
        else output << min << "   ";
    } 
    
    hour = session.end/60;
    min = session.end - hour * 60;
    output << hour << ":";
    if(min < 10) output<< "0" << min << std::endl;
    else output << min << std::endl;
}

void find_solution(int j){ // find solution for best_for_eachplace and add them to sessions_tow(to write)
    if(j == -1) return;
    else if(sessions[j].cap + mem[p[j]+1] > mem[j]){
        sessions_tow.push_back(sessions[j]);
        std::rotate(sessions_tow.rbegin(), sessions_tow.rbegin() + 1, sessions_tow.rend());
        return find_solution(p[j]);
    }
    else return find_solution(j-1);
}

void write_sessions_tour(Session session, std::ofstream & output){ // write sessions to best_tour.txt
    int month, day, w;
    
    output << std::left << std::setw(16) << session.place;

    month = session.start/31;
    day = session.start - month * 31;

    output << months[month-1] << " ";
    if(month == 5) w = 4;
    else w = 3;

    output << std::setw(w) << day;

    month = session.end/31;
    day = session.end - month * 31;

    output << months[month-1] << " ";
    output << day << std::endl;
}

void find_solution_tour(int j){ // find solution for best_tour and add them to sessions_tow(to write)
    if(j == -1) return;
    else if(places[j].cap + mem[p[j]+1] > mem[j]){
        sessions_tow.push_back(places[j]);
        std::rotate(sessions_tow.rbegin(), sessions_tow.rbegin() + 1, sessions_tow.rend());
        return find_solution_tour(p[j]);
    }
    else return find_solution_tour(j-1);
}

int main(int argc, char *argv[]){
    std::fstream daily_schedule;  
    std::fstream capacity;  
    std::fstream availability_intervals;  
    std::fstream assets; 
    std::ofstream output_eachplace("outputs/case_" + (std::string)argv[1] + "/best_for_eachplace.txt"); 
    std::ofstream output_besttour("outputs/case_" + (std::string)argv[1] + "/best_tour.txt");
    std::ofstream output_upgrade_list("outputs/case_" + (std::string)argv[1] + "/upgrade_list.txt"); // open all input and output files

    daily_schedule.open("inputs/case_" + (std::string)argv[1] + "/daily_schedule.txt");
    capacity.open("inputs/case_" + (std::string)argv[1] + "/capacity.txt");
    availability_intervals.open("inputs/case_" + (std::string)argv[1] + "/availability_intervals.txt");
    assets.open("inputs/case_" + (std::string)argv[1] + "/assets.txt"); // read input files
    
    std::string c;
    if (assets.is_open() && daily_schedule.is_open() && capacity.is_open() && availability_intervals.is_open()){
       std::getline(capacity, c);
       std::getline(daily_schedule, c);

        std::string loc;
        std::string place = "";
        int cap;

        std::string p_in = "";
        std::string loc_in;
        std::string saloon_in;
        int capacity_in;
        int start_in;
        int end_in;

        std::string p_in_tmp;
        std::string saloon_in_tmp; 
        int capacity_in_tmp; 
        int start_in_tmp;
        int end_in_tmp;
        std::string tmp;

        int max_cap_temp;
        int hour;
        bool changed_first_row = false;

        std::vector<std::tuple<std::string, int>> locations;

        // read daily_schedule.txt and capacity.txt and combine them to form sessions vector holds all the information
        while(getline(capacity, c, ' ')){
            tmp = c;
            if(place != "" && place != c){
                while(getline(daily_schedule, c, ' ')){
                    if(changed_first_row){
                        sessions.push_back(Session(p_in_tmp, saloon_in_tmp, capacity_in_tmp, start_in_tmp, end_in_tmp));
                        changed_first_row = false;
                    }
                    if(p_in != "" && p_in != c){
                        changed_first_row = true;
                    }
                    p_in = c;
                    getline(daily_schedule, c, ' ');
                    saloon_in = c;
                    loc_in = p_in + " " + saloon_in;
                    for (const auto& t : locations) {
                        if(std::get<0>(t) == loc_in){
                            capacity_in = std::get<1>(t);
                            break;
                        }
                    }
                    getline(daily_schedule, c, ':');
                    hour = stoi(c);
                    getline(daily_schedule, c, ' ');
                    start_in = hour * 60 + stoi(c);
                    getline(daily_schedule, c, ':');
                    hour = stoi(c);
                    getline(daily_schedule, c, '\n');
                    end_in = hour * 60 + stoi(c);
                    if(!changed_first_row) sessions.push_back(Session(p_in, saloon_in, capacity_in, start_in, end_in));
                    else{
                        p_in_tmp = p_in;
                        saloon_in_tmp = saloon_in;
                        start_in_tmp = start_in;
                        end_in_tmp = end_in;
                        break;
                    }
                }

                max_cap_temp = top_down(output_eachplace);
                places.push_back(Session(sessions[0].place, max_cap_temp));
                output_eachplace << max_cap_temp << std::endl;
                find_solution(sessions.size()-1);
                for (const auto& t : sessions_tow) {
                    write_sessions(t, output_eachplace);
                }
                output_eachplace << std::endl;
                
                sessions_tow.clear();
                mem.clear();
                p.clear();
                sessions.clear();
                locations.clear();

                c = tmp;
            }
            place = c;
            loc = c;
            getline(capacity, c, ' ');
            loc = loc + " " + c;
            getline(capacity, c, '\n');
            cap = stoi(c);
            locations.push_back(make_tuple(loc, cap));
            if(changed_first_row){
                for (const auto& t : locations) {
                    if(std::get<0>(t) == p_in_tmp + " " + saloon_in_tmp){
                        capacity_in_tmp = std::get<1>(t);
                        break;
                    }
                }
            }
        }

        while(getline(daily_schedule, c, ' ')){
            if(changed_first_row){
                sessions.push_back(Session(p_in_tmp, saloon_in_tmp, capacity_in_tmp, start_in_tmp, end_in_tmp));
                changed_first_row = false;
            }

            if(p_in != "" && p_in != c) changed_first_row = true;
    
            p_in = c;
            getline(daily_schedule, c, ' ');
            saloon_in = c;
            loc_in = p_in + " " + saloon_in;
            for (const auto& t : locations) {
                if(std::get<0>(t) == loc_in){
                    capacity_in = std::get<1>(t);
                    break;
                }
            }
            getline(daily_schedule, c, ':');
            hour = stoi(c);
            getline(daily_schedule, c, ' ');
            start_in = hour * 60 + stoi(c);
            getline(daily_schedule, c, ':');
            hour = stoi(c);
            getline(daily_schedule, c, '\n');
            end_in = hour * 60 + stoi(c);
            if(!changed_first_row) sessions.push_back(Session(p_in, saloon_in, capacity_in, start_in, end_in));
            else{
                p_in_tmp = p_in;
                saloon_in_tmp = saloon_in;
                capacity_in_tmp = capacity_in;
                start_in_tmp = start_in;
                end_in_tmp = end_in;
                break;
            }
        }

        max_cap_temp = top_down(output_eachplace); // run top down weighted interval scheduling algorithm for sessions vector  
        places.push_back(Session(sessions[0].place, max_cap_temp));
        output_eachplace << max_cap_temp << std::endl;
        find_solution(sessions.size()-1); //find solution
        for (const auto& t : sessions_tow) {
            write_sessions(t, output_eachplace); // and write to output file
        }
        output_eachplace << std::endl;

        sessions_tow.clear();
        mem.clear();
        p.clear();
        sessions.clear();
        locations.clear();

        getline(availability_intervals, c); // read availability_intervals.txt to form places vector that holds all information

        int day,month,s,e, i = 0;
        Session t;
        bool is_first;
        getline(availability_intervals, c, ' ');
        while(i < (int)places.size()){
            t = places[i];
            is_first = true;
            while(1){
                if(c == t.place){
                    getline(availability_intervals, c, '.');
                    day = stoi(c);
                    getline(availability_intervals, c, ' ');
                    month = stoi(c);
                    s = 31 * month + day;
                    getline(availability_intervals, c, '.');
                    day = stoi(c);
                    getline(availability_intervals, c, '\n');
                    month = stoi(c);
                    e = 31 * month + day;
                    if(is_first){
                        places[i].start = s;
                        places[i].end = e;
                        places[i].cap = (places[i].end - places[i].start) * places[i].cap;
                        is_first = false;
                    }else{
                        places.push_back(Session(t.place, t.cap * (e-s), s, e));
                    }
                    getline(availability_intervals, c, ' ');
                } else break;
            }
            i++;
        }

        int revenue = top_down_tour(output_besttour); // run top down weighted interval scheduling for places vector 
        output_besttour << revenue << std::endl;
        find_solution_tour(places.size()-1); // find solution

        for (const auto& t : sessions_tow) {
            write_sessions_tour(t, output_besttour); // and write to best_tour.txt
        }

        sessions_tow.clear();
        mem.clear();
        p.clear();
        sessions.clear();
        locations.clear();

        getline(assets, c); // read according to the input assets format

        std::vector<Asset> asset_list;
        int p, num_of_assets = 0;
        std::string na;
        while(getline(assets, c, ' ')){
            na = c;
            getline(assets, c, ' ');
            p = stoi(c);
            getline(assets, c, '\n');
            asset_list.push_back(Asset(na,p,stod(c)));
            num_of_assets++;
        }

        knap_sack(revenue, num_of_assets, asset_list, output_upgrade_list); // run knapsack algorithm for this revenue and asset_list
    }

    assets.close();     // close all files and exit
    daily_schedule.close();  
    capacity.close();  
    availability_intervals.close(); 
    output_eachplace.close();
    output_besttour.close();
    output_upgrade_list.close();

    exit(0);
}