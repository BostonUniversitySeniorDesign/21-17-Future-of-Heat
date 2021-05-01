


$(function() {
    var chart2 = new Chartist.Line('.campaign2', {
        labels: ['House 1', 'House 2', 'House 3', 'House 4', 'House 5', 'House 6','House 7', 'House 8', 'House 9', 'House 10', 'House 11', 'Hotel'],
        series: [
            {color:'#581845', data:[0, 5, 6, 8, 25, 9, 8, 24, 12, 10, 12, 5]},
            {color:'#581845', data: [0, 3, 1, 2, 8, 1, 5, 1, 20 , 16, 10, 11]}
        ]
    }, {
        low: 0,
        high: 50,
        showArea: true,
        fullWidth: false,
        plugins: [
            Chartist.plugins.tooltip()
        ],
        axisX: {
            title: 'Load'
        }
        ,
        axisY: {
            title: 'Load',
            onlyInteger: true,
            scaleMinSpace: 20,
            offset: 2,
            labelInterpolationFnc: function(value) {

                return (value / 1) + 'W';
            }
        },

         chartPadding: {
                left: 30,
                right: 0,
                top: 0,
                bottom: 0
            }

    });

    // Offset x1 a tiny amount so that the straight stroke gets a bounding box
    // Straight lines don't get a bounding box 
    // Last remark on -> http://www.w3.org/TR/SVG11/coords.html#ObjectBoundingBox
    chart2.on('draw', function(ctx) {
        if (ctx.type === 'area') {
            ctx.element.attr({
                x1: ctx.x1 + 0.001
            });
        }
    });

    // Create the gradient definition on created event (always after chart re-render)
    chart2.on('created', function(ctx) {
        var defs = ctx.svg.elem('defs');
        defs.elem('linearGradient', {
            id: 'gradient',
            x1: 0,
            y1: 1,
            x2: 0,
            y2: 0
        }).elem('stop', {
            offset: 0,
            'stop-color': 'rgba(255, 255, 255, 1)'
        }).parent().elem('stop', {
            offset: 1,
            'stop-color': 'rgba(64, 196, 255, 1)'
        });
    });


    var chart2 = [chart2];
});

  